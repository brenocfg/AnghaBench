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
struct shallow_info {int dummy; } ;
struct ref {int dummy; } ;
struct oid_array {scalar_t__ nr; } ;
struct TYPE_2__ {int /*<<< orphan*/  choice; } ;
struct fetch_pack_args {int connectivity_checked; scalar_t__ deepen; int /*<<< orphan*/  cloning; TYPE_1__ filter_options; scalar_t__ no_dependents; } ;
struct check_connected_options {int is_deepening_fetch; int /*<<< orphan*/  shallow_file; } ;
typedef  int /*<<< orphan*/  si ;
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 struct oid_array OID_ARRAY_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  alternate_shallow_file ; 
 scalar_t__ check_connected (int /*<<< orphan*/ ,struct ref**,struct check_connected_options*) ; 
 int /*<<< orphan*/  clear_shallow_info (struct shallow_info*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 struct ref* do_fetch_pack (struct fetch_pack_args*,int*,struct ref const*,struct ref**,int,struct shallow_info*,char**) ; 
 struct ref* do_fetch_pack_v2 (struct fetch_pack_args*,int*,struct ref const*,struct ref**,int,struct oid_array*,struct shallow_info*,char**) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_pack_setup () ; 
 int /*<<< orphan*/  free_refs (struct ref*) ; 
 int /*<<< orphan*/  iterate_ref_map ; 
 int /*<<< orphan*/  memset (struct shallow_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  parse_list_objects_filter (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  prepare_shallow_info (struct shallow_info*,struct oid_array*) ; 
 int protocol_v2 ; 
 int remove_duplicates_in_refs (struct ref**,int) ; 
 int /*<<< orphan*/  reprepare_packed_git (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shallow_lock ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  update_shallow (struct fetch_pack_args*,struct ref**,int,struct shallow_info*) ; 

struct ref *fetch_pack(struct fetch_pack_args *args,
		       int fd[],
		       const struct ref *ref,
		       struct ref **sought, int nr_sought,
		       struct oid_array *shallow,
		       char **pack_lockfile,
		       enum protocol_version version)
{
	struct ref *ref_cpy;
	struct shallow_info si;
	struct oid_array shallows_scratch = OID_ARRAY_INIT;

	fetch_pack_setup();
	if (nr_sought)
		nr_sought = remove_duplicates_in_refs(sought, nr_sought);

	if (args->no_dependents && !args->filter_options.choice) {
		/*
		 * The protocol does not support requesting that only the
		 * wanted objects be sent, so approximate this by setting a
		 * "blob:none" filter if no filter is already set. This works
		 * for all object types: note that wanted blobs will still be
		 * sent because they are directly specified as a "want".
		 *
		 * NEEDSWORK: Add an option in the protocol to request that
		 * only the wanted objects be sent, and implement it.
		 */
		parse_list_objects_filter(&args->filter_options, "blob:none");
	}

	if (version != protocol_v2 && !ref) {
		packet_flush(fd[1]);
		die(_("no matching remote head"));
	}
	if (version == protocol_v2) {
		if (shallow->nr)
			BUG("Protocol V2 does not provide shallows at this point in the fetch");
		memset(&si, 0, sizeof(si));
		ref_cpy = do_fetch_pack_v2(args, fd, ref, sought, nr_sought,
					   &shallows_scratch, &si,
					   pack_lockfile);
	} else {
		prepare_shallow_info(&si, shallow);
		ref_cpy = do_fetch_pack(args, fd, ref, sought, nr_sought,
					&si, pack_lockfile);
	}
	reprepare_packed_git(the_repository);

	if (!args->cloning && args->deepen) {
		struct check_connected_options opt = CHECK_CONNECTED_INIT;
		struct ref *iterator = ref_cpy;
		opt.shallow_file = alternate_shallow_file;
		if (args->deepen)
			opt.is_deepening_fetch = 1;
		if (check_connected(iterate_ref_map, &iterator, &opt)) {
			error(_("remote did not send all necessary objects"));
			free_refs(ref_cpy);
			ref_cpy = NULL;
			rollback_lock_file(&shallow_lock);
			goto cleanup;
		}
		args->connectivity_checked = 1;
	}

	update_shallow(args, sought, nr_sought, &si);
cleanup:
	clear_shallow_info(&si);
	oid_array_clear(&shallows_scratch);
	return ref_cpy;
}