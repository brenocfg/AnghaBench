#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shallow_info {int /*<<< orphan*/  shallow; scalar_t__ nr_theirs; scalar_t__ nr_ours; } ;
struct repository {int dummy; } ;
struct ref {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ choice; } ;
struct fetch_pack_args {scalar_t__ depth; int deepen; scalar_t__ stateless_rpc; int /*<<< orphan*/  keep_pack; int /*<<< orphan*/  no_dependents; scalar_t__ deepen_relative; scalar_t__ deepen_not; scalar_t__ deepen_since; TYPE_1__ filter_options; scalar_t__ include_tag; scalar_t__ no_progress; scalar_t__ use_thin_pack; } ;
struct fetch_negotiator {int /*<<< orphan*/  (* release ) (struct fetch_negotiator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_REACHABLE_SHA1 ; 
 int /*<<< orphan*/  ALLOW_TIP_SHA1 ; 
 int /*<<< orphan*/  QSORT (struct ref**,int,int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int agent_supported ; 
 int /*<<< orphan*/  allow_unadvertised_object_request ; 
 int /*<<< orphan*/ * alternate_shallow_file ; 
 int /*<<< orphan*/  cmp_ref_by_name ; 
 struct ref* copy_ref_list (struct ref const*) ; 
 int deepen_not_ok ; 
 int deepen_since_ok ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ everything_local (struct fetch_pack_args*,struct ref**) ; 
 int /*<<< orphan*/  fetch_negotiator_init (struct repository*,struct fetch_negotiator*) ; 
 int /*<<< orphan*/  filter_refs (struct fetch_pack_args*,struct ref**,struct ref**,int) ; 
 scalar_t__ find_common (struct fetch_negotiator*,struct fetch_pack_args*,int*,struct object_id*,struct ref*) ; 
 scalar_t__ get_pack (struct fetch_pack_args*,int*,char**,struct ref**,int) ; 
 scalar_t__ is_repository_shallow (struct repository*) ; 
 int /*<<< orphan*/  mark_complete_and_common_ref (struct fetch_negotiator*,struct fetch_pack_args*,struct ref**) ; 
 int multi_ack ; 
 int no_done ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 scalar_t__ prefer_ofs_delta ; 
 int /*<<< orphan*/  print_verbose (struct fetch_pack_args*,char*,...) ; 
 int /*<<< orphan*/  ref_compare_name ; 
 char* server_feature_value (char*,int*) ; 
 scalar_t__ server_supports (char*) ; 
 int server_supports_filtering ; 
 int /*<<< orphan*/  setup_alternate_shallow (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_temporary_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shallow_lock ; 
 int /*<<< orphan*/  sort_ref_list (struct ref**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fetch_negotiator*) ; 
 struct repository* the_repository ; 
 int use_sideband ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static struct ref *do_fetch_pack(struct fetch_pack_args *args,
				 int fd[2],
				 const struct ref *orig_ref,
				 struct ref **sought, int nr_sought,
				 struct shallow_info *si,
				 char **pack_lockfile)
{
	struct repository *r = the_repository;
	struct ref *ref = copy_ref_list(orig_ref);
	struct object_id oid;
	const char *agent_feature;
	int agent_len;
	struct fetch_negotiator negotiator;
	fetch_negotiator_init(r, &negotiator);

	sort_ref_list(&ref, ref_compare_name);
	QSORT(sought, nr_sought, cmp_ref_by_name);

	if ((agent_feature = server_feature_value("agent", &agent_len))) {
		agent_supported = 1;
		if (agent_len)
			print_verbose(args, _("Server version is %.*s"),
				      agent_len, agent_feature);
	}

	if (server_supports("shallow"))
		print_verbose(args, _("Server supports %s"), "shallow");
	else if (args->depth > 0 || is_repository_shallow(r))
		die(_("Server does not support shallow clients"));
	if (args->depth > 0 || args->deepen_since || args->deepen_not)
		args->deepen = 1;
	if (server_supports("multi_ack_detailed")) {
		print_verbose(args, _("Server supports %s"), "multi_ack_detailed");
		multi_ack = 2;
		if (server_supports("no-done")) {
			print_verbose(args, _("Server supports %s"), "no-done");
			if (args->stateless_rpc)
				no_done = 1;
		}
	}
	else if (server_supports("multi_ack")) {
		print_verbose(args, _("Server supports %s"), "multi_ack");
		multi_ack = 1;
	}
	if (server_supports("side-band-64k")) {
		print_verbose(args, _("Server supports %s"), "side-band-64k");
		use_sideband = 2;
	}
	else if (server_supports("side-band")) {
		print_verbose(args, _("Server supports %s"), "side-band");
		use_sideband = 1;
	}
	if (server_supports("allow-tip-sha1-in-want")) {
		print_verbose(args, _("Server supports %s"), "allow-tip-sha1-in-want");
		allow_unadvertised_object_request |= ALLOW_TIP_SHA1;
	}
	if (server_supports("allow-reachable-sha1-in-want")) {
		print_verbose(args, _("Server supports %s"), "allow-reachable-sha1-in-want");
		allow_unadvertised_object_request |= ALLOW_REACHABLE_SHA1;
	}
	if (server_supports("thin-pack"))
		print_verbose(args, _("Server supports %s"), "thin-pack");
	else
		args->use_thin_pack = 0;
	if (server_supports("no-progress"))
		print_verbose(args, _("Server supports %s"), "no-progress");
	else
		args->no_progress = 0;
	if (server_supports("include-tag"))
		print_verbose(args, _("Server supports %s"), "include-tag");
	else
		args->include_tag = 0;
	if (server_supports("ofs-delta"))
		print_verbose(args, _("Server supports %s"), "ofs-delta");
	else
		prefer_ofs_delta = 0;

	if (server_supports("filter")) {
		server_supports_filtering = 1;
		print_verbose(args, _("Server supports %s"), "filter");
	} else if (args->filter_options.choice) {
		warning("filtering not recognized by server, ignoring");
	}

	if (server_supports("deepen-since")) {
		print_verbose(args, _("Server supports %s"), "deepen-since");
		deepen_since_ok = 1;
	} else if (args->deepen_since)
		die(_("Server does not support --shallow-since"));
	if (server_supports("deepen-not")) {
		print_verbose(args, _("Server supports %s"), "deepen-not");
		deepen_not_ok = 1;
	} else if (args->deepen_not)
		die(_("Server does not support --shallow-exclude"));
	if (server_supports("deepen-relative"))
		print_verbose(args, _("Server supports %s"), "deepen-relative");
	else if (args->deepen_relative)
		die(_("Server does not support --deepen"));

	if (!args->no_dependents) {
		mark_complete_and_common_ref(&negotiator, args, &ref);
		filter_refs(args, &ref, sought, nr_sought);
		if (everything_local(args, &ref)) {
			packet_flush(fd[1]);
			goto all_done;
		}
	} else {
		filter_refs(args, &ref, sought, nr_sought);
	}
	if (find_common(&negotiator, args, fd, &oid, ref) < 0)
		if (!args->keep_pack)
			/* When cloning, it is not unusual to have
			 * no common commit.
			 */
			warning(_("no common commits"));

	if (args->stateless_rpc)
		packet_flush(fd[1]);
	if (args->deepen)
		setup_alternate_shallow(&shallow_lock, &alternate_shallow_file,
					NULL);
	else if (si->nr_ours || si->nr_theirs)
		alternate_shallow_file = setup_temporary_shallow(si->shallow);
	else
		alternate_shallow_file = NULL;
	if (get_pack(args, fd, pack_lockfile, sought, nr_sought))
		die(_("git fetch-pack: fetch failed."));

 all_done:
	negotiator.release(&negotiator);
	return ref;
}