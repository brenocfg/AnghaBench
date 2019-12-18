#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct shallow_info {int dummy; } ;
struct repository {int dummy; } ;
struct ref {int dummy; } ;
struct packet_reader {int use_sideband; char* me; } ;
struct oidset {int dummy; } ;
struct oid_array {int dummy; } ;
struct fetch_pack_args {int deepen; int /*<<< orphan*/  negotiation_tips; int /*<<< orphan*/  no_dependents; int /*<<< orphan*/  deepen_not; int /*<<< orphan*/  deepen_since; int /*<<< orphan*/  depth; } ;
struct fetch_negotiator {int /*<<< orphan*/  (* release ) (struct fetch_negotiator*) ;} ;
typedef  enum fetch_state { ____Placeholder_fetch_state } fetch_state ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_REACHABLE_SHA1 ; 
#define  FETCH_CHECK_LOCAL 132 
#define  FETCH_DONE 131 
#define  FETCH_GET_PACK 130 
#define  FETCH_PROCESS_ACKS 129 
#define  FETCH_SEND_REQUEST 128 
 int INITIAL_FLUSH ; 
 struct oidset OIDSET_INIT ; 
 int PACKET_READ_CHOMP_NEWLINE ; 
 int PACKET_READ_DIE_ON_ERR_PACKET ; 
 int /*<<< orphan*/  QSORT (struct ref**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  allow_unadvertised_object_request ; 
 int /*<<< orphan*/  cmp_ref_by_name ; 
 struct ref* copy_ref_list (struct ref const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  everything_local (struct fetch_pack_args*,struct ref**) ; 
 int /*<<< orphan*/  fetch_negotiator_init (struct repository*,struct fetch_negotiator*) ; 
 int /*<<< orphan*/  filter_refs (struct fetch_pack_args*,struct ref**,struct ref**,int) ; 
 int /*<<< orphan*/  for_each_cached_alternate (struct fetch_negotiator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pack (struct fetch_pack_args*,int*,char**,struct ref**,int) ; 
 scalar_t__ git_env_bool (char*,int) ; 
 int /*<<< orphan*/  insert_one_alternate_object ; 
 int /*<<< orphan*/  mark_complete_and_common_ref (struct fetch_negotiator*,struct fetch_pack_args*,struct ref**) ; 
 int /*<<< orphan*/  mark_tips (struct fetch_negotiator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidset_clear (struct oidset*) ; 
 int /*<<< orphan*/  packet_reader_init (struct packet_reader*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_acks (struct fetch_negotiator*,struct packet_reader*,struct oidset*) ; 
 int /*<<< orphan*/  process_section_header (struct packet_reader*,char*,int) ; 
 int /*<<< orphan*/  receive_shallow_info (struct fetch_pack_args*,struct packet_reader*,struct oid_array*,struct shallow_info*) ; 
 int /*<<< orphan*/  receive_wanted_refs (struct packet_reader*,struct ref**,int) ; 
 int /*<<< orphan*/  ref_compare_name ; 
 int /*<<< orphan*/  send_fetch_request (struct fetch_negotiator*,int,struct fetch_pack_args*,struct ref*,struct oidset*,int*,int*,int) ; 
 scalar_t__ server_supports_feature (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_ref_list (struct ref**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fetch_negotiator*) ; 
 struct repository* the_repository ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,struct repository*) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,struct repository*) ; 
 int use_sideband ; 

__attribute__((used)) static struct ref *do_fetch_pack_v2(struct fetch_pack_args *args,
				    int fd[2],
				    const struct ref *orig_ref,
				    struct ref **sought, int nr_sought,
				    struct oid_array *shallows,
				    struct shallow_info *si,
				    char **pack_lockfile)
{
	struct repository *r = the_repository;
	struct ref *ref = copy_ref_list(orig_ref);
	enum fetch_state state = FETCH_CHECK_LOCAL;
	struct oidset common = OIDSET_INIT;
	struct packet_reader reader;
	int in_vain = 0, negotiation_started = 0;
	int haves_to_send = INITIAL_FLUSH;
	struct fetch_negotiator negotiator;
	fetch_negotiator_init(r, &negotiator);
	packet_reader_init(&reader, fd[0], NULL, 0,
			   PACKET_READ_CHOMP_NEWLINE |
			   PACKET_READ_DIE_ON_ERR_PACKET);
	if (git_env_bool("GIT_TEST_SIDEBAND_ALL", 1) &&
	    server_supports_feature("fetch", "sideband-all", 0)) {
		reader.use_sideband = 1;
		reader.me = "fetch-pack";
	}

	while (state != FETCH_DONE) {
		switch (state) {
		case FETCH_CHECK_LOCAL:
			sort_ref_list(&ref, ref_compare_name);
			QSORT(sought, nr_sought, cmp_ref_by_name);

			/* v2 supports these by default */
			allow_unadvertised_object_request |= ALLOW_REACHABLE_SHA1;
			use_sideband = 2;
			if (args->depth > 0 || args->deepen_since || args->deepen_not)
				args->deepen = 1;

			/* Filter 'ref' by 'sought' and those that aren't local */
			if (!args->no_dependents) {
				mark_complete_and_common_ref(&negotiator, args, &ref);
				filter_refs(args, &ref, sought, nr_sought);
				if (everything_local(args, &ref))
					state = FETCH_DONE;
				else
					state = FETCH_SEND_REQUEST;

				mark_tips(&negotiator, args->negotiation_tips);
				for_each_cached_alternate(&negotiator,
							  insert_one_alternate_object);
			} else {
				filter_refs(args, &ref, sought, nr_sought);
				state = FETCH_SEND_REQUEST;
			}
			break;
		case FETCH_SEND_REQUEST:
			if (!negotiation_started) {
				negotiation_started = 1;
				trace2_region_enter("fetch-pack",
						    "negotiation_v2",
						    the_repository);
			}
			if (send_fetch_request(&negotiator, fd[1], args, ref,
					       &common,
					       &haves_to_send, &in_vain,
					       reader.use_sideband))
				state = FETCH_GET_PACK;
			else
				state = FETCH_PROCESS_ACKS;
			break;
		case FETCH_PROCESS_ACKS:
			/* Process ACKs/NAKs */
			switch (process_acks(&negotiator, &reader, &common)) {
			case 2:
				state = FETCH_GET_PACK;
				break;
			case 1:
				in_vain = 0;
				/* fallthrough */
			default:
				state = FETCH_SEND_REQUEST;
				break;
			}
			break;
		case FETCH_GET_PACK:
			trace2_region_leave("fetch-pack",
					    "negotiation_v2",
					    the_repository);
			/* Check for shallow-info section */
			if (process_section_header(&reader, "shallow-info", 1))
				receive_shallow_info(args, &reader, shallows, si);

			if (process_section_header(&reader, "wanted-refs", 1))
				receive_wanted_refs(&reader, sought, nr_sought);

			/* get the pack */
			process_section_header(&reader, "packfile", 0);
			if (get_pack(args, fd, pack_lockfile, sought, nr_sought))
				die(_("git fetch-pack: fetch failed."));

			state = FETCH_DONE;
			break;
		case FETCH_DONE:
			continue;
		}
	}

	negotiator.release(&negotiator);
	oidset_clear(&common);
	return ref;
}