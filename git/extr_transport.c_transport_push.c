#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct transport {TYPE_3__* remote; int /*<<< orphan*/  url; TYPE_2__* vtable; int /*<<< orphan*/  push_options; TYPE_1__* smart_options; int /*<<< orphan*/  verbose; } ;
struct string_list {int dummy; } ;
struct repository {int dummy; } ;
struct refspec {int dummy; } ;
struct ref {int status; struct ref* next; int /*<<< orphan*/  new_oid; } ;
struct oid_array {int dummy; } ;
struct argv_array {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int (* push_refs ) (struct transport*,struct ref*,int) ;struct ref* (* get_refs_list ) (struct transport*,int,struct argv_array*) ;} ;
struct TYPE_6__ {scalar_t__ cas; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int MATCH_REFS_ALL ; 
 int MATCH_REFS_FOLLOW_TAGS ; 
 int MATCH_REFS_MIRROR ; 
 int MATCH_REFS_NONE ; 
 int MATCH_REFS_PRUNE ; 
 struct oid_array OID_ARRAY_INIT ; 
 int REF_STATUS_ATOMIC_PUSH_FAILED ; 
#define  REF_STATUS_NONE 130 
#define  REF_STATUS_OK 129 
#define  REF_STATUS_UPTODATE 128 
 struct string_list STRING_LIST_INIT_DUP ; 
 int TRANSPORT_PUSH_ALL ; 
 int TRANSPORT_PUSH_ATOMIC ; 
 int TRANSPORT_PUSH_DRY_RUN ; 
 int TRANSPORT_PUSH_FOLLOW_TAGS ; 
 int TRANSPORT_PUSH_FORCE ; 
 int TRANSPORT_PUSH_MIRROR ; 
 int TRANSPORT_PUSH_NO_HOOK ; 
 int TRANSPORT_PUSH_PORCELAIN ; 
 int TRANSPORT_PUSH_PRUNE ; 
 int TRANSPORT_PUSH_SET_UPSTREAM ; 
 int TRANSPORT_RECURSE_SUBMODULES_CHECK ; 
 int TRANSPORT_RECURSE_SUBMODULES_ONLY ; 
 int TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apply_push_cas (scalar_t__,TYPE_3__*,struct ref*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 scalar_t__ check_push_refs (struct ref*,struct refspec*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_with_unpushed_submodules (struct string_list*) ; 
 scalar_t__ find_unpushed_submodules (struct repository*,struct oid_array*,int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct ref* get_local_heads () ; 
 int /*<<< orphan*/  is_bare_repository () ; 
 int /*<<< orphan*/  is_empty_cas (scalar_t__) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ match_push_refs (struct ref*,struct ref**,struct refspec*,int) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int push_had_errors (struct ref*) ; 
 int /*<<< orphan*/  push_unpushed_submodules (struct repository*,struct oid_array*,TYPE_3__*,struct refspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  refspec_ref_prefixes (struct refspec*,struct argv_array*) ; 
 scalar_t__ run_pre_push_hook (struct transport*,struct ref*) ; 
 int /*<<< orphan*/  set_ref_status_for_push (struct ref*,int,int) ; 
 int /*<<< orphan*/  set_upstreams (struct transport*,struct ref*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 struct ref* stub1 (struct transport*,int,struct argv_array*) ; 
 int stub2 (struct transport*,struct ref*,int) ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,struct repository*) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,struct repository*) ; 
 scalar_t__ transport_color_config () ; 
 int /*<<< orphan*/  transport_print_push_status (int /*<<< orphan*/ ,struct ref*,int,int,unsigned int*) ; 
 int /*<<< orphan*/  transport_refs_pushed (struct ref*) ; 
 int /*<<< orphan*/  transport_update_tracking_ref (TYPE_3__*,struct ref*,int) ; 

int transport_push(struct repository *r,
		   struct transport *transport,
		   struct refspec *rs, int flags,
		   unsigned int *reject_reasons)
{
	*reject_reasons = 0;

	if (transport_color_config() < 0)
		return -1;

	if (transport->vtable->push_refs) {
		struct ref *remote_refs;
		struct ref *local_refs = get_local_heads();
		int match_flags = MATCH_REFS_NONE;
		int verbose = (transport->verbose > 0);
		int quiet = (transport->verbose < 0);
		int porcelain = flags & TRANSPORT_PUSH_PORCELAIN;
		int pretend = flags & TRANSPORT_PUSH_DRY_RUN;
		int push_ret, ret, err;
		struct argv_array ref_prefixes = ARGV_ARRAY_INIT;

		if (check_push_refs(local_refs, rs) < 0)
			return -1;

		refspec_ref_prefixes(rs, &ref_prefixes);

		trace2_region_enter("transport_push", "get_refs_list", r);
		remote_refs = transport->vtable->get_refs_list(transport, 1,
							       &ref_prefixes);
		trace2_region_leave("transport_push", "get_refs_list", r);

		argv_array_clear(&ref_prefixes);

		if (flags & TRANSPORT_PUSH_ALL)
			match_flags |= MATCH_REFS_ALL;
		if (flags & TRANSPORT_PUSH_MIRROR)
			match_flags |= MATCH_REFS_MIRROR;
		if (flags & TRANSPORT_PUSH_PRUNE)
			match_flags |= MATCH_REFS_PRUNE;
		if (flags & TRANSPORT_PUSH_FOLLOW_TAGS)
			match_flags |= MATCH_REFS_FOLLOW_TAGS;

		if (match_push_refs(local_refs, &remote_refs, rs, match_flags))
			return -1;

		if (transport->smart_options &&
		    transport->smart_options->cas &&
		    !is_empty_cas(transport->smart_options->cas))
			apply_push_cas(transport->smart_options->cas,
				       transport->remote, remote_refs);

		set_ref_status_for_push(remote_refs,
			flags & TRANSPORT_PUSH_MIRROR,
			flags & TRANSPORT_PUSH_FORCE);

		if (!(flags & TRANSPORT_PUSH_NO_HOOK))
			if (run_pre_push_hook(transport, remote_refs))
				return -1;

		if ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
			      TRANSPORT_RECURSE_SUBMODULES_ONLY)) &&
		    !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct oid_array commits = OID_ARRAY_INIT;

			trace2_region_enter("transport_push", "push_submodules", r);
			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					oid_array_append(&commits,
							  &ref->new_oid);

			if (!push_unpushed_submodules(r,
						      &commits,
						      transport->remote,
						      rs,
						      transport->push_options,
						      pretend)) {
				oid_array_clear(&commits);
				trace2_region_leave("transport_push", "push_submodules", r);
				die(_("failed to push all needed submodules"));
			}
			oid_array_clear(&commits);
			trace2_region_leave("transport_push", "push_submodules", r);
		}

		if (((flags & TRANSPORT_RECURSE_SUBMODULES_CHECK) ||
		     ((flags & (TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND |
				TRANSPORT_RECURSE_SUBMODULES_ONLY)) &&
		      !pretend)) && !is_bare_repository()) {
			struct ref *ref = remote_refs;
			struct string_list needs_pushing = STRING_LIST_INIT_DUP;
			struct oid_array commits = OID_ARRAY_INIT;

			trace2_region_enter("transport_push", "check_submodules", r);
			for (; ref; ref = ref->next)
				if (!is_null_oid(&ref->new_oid))
					oid_array_append(&commits,
							  &ref->new_oid);

			if (find_unpushed_submodules(r,
						     &commits,
						     transport->remote->name,
						     &needs_pushing)) {
				oid_array_clear(&commits);
				trace2_region_leave("transport_push", "check_submodules", r);
				die_with_unpushed_submodules(&needs_pushing);
			}
			string_list_clear(&needs_pushing, 0);
			oid_array_clear(&commits);
			trace2_region_leave("transport_push", "check_submodules", r);
		}

		if (!(flags & TRANSPORT_RECURSE_SUBMODULES_ONLY)) {
			trace2_region_enter("transport_push", "push_refs", r);
			push_ret = transport->vtable->push_refs(transport, remote_refs, flags);
			trace2_region_leave("transport_push", "push_refs", r);
		} else
			push_ret = 0;
		err = push_had_errors(remote_refs);
		ret = push_ret | err;

		if ((flags & TRANSPORT_PUSH_ATOMIC) && err) {
			struct ref *it;
			for (it = remote_refs; it; it = it->next)
				switch (it->status) {
				case REF_STATUS_NONE:
				case REF_STATUS_UPTODATE:
				case REF_STATUS_OK:
					it->status = REF_STATUS_ATOMIC_PUSH_FAILED;
					break;
				default:
					break;
				}
		}

		if (!quiet || err)
			transport_print_push_status(transport->url, remote_refs,
					verbose | porcelain, porcelain,
					reject_reasons);

		if (flags & TRANSPORT_PUSH_SET_UPSTREAM)
			set_upstreams(transport, remote_refs, pretend);

		if (!(flags & (TRANSPORT_PUSH_DRY_RUN |
			       TRANSPORT_RECURSE_SUBMODULES_ONLY))) {
			struct ref *ref;
			for (ref = remote_refs; ref; ref = ref->next)
				transport_update_tracking_ref(transport->remote, ref, verbose);
		}

		if (porcelain && !push_ret)
			puts("Done");
		else if (!quiet && !ret && !transport_refs_pushed(remote_refs))
			fprintf(stderr, "Everything up-to-date\n");

		return ret;
	}
	return 1;
}