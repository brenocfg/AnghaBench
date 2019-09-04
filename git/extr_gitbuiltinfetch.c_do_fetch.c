#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct transport {int /*<<< orphan*/  url; TYPE_2__* remote; } ;
struct refspec {int nr; TYPE_1__* items; } ;
struct ref {int dummy; } ;
struct argv_array {scalar_t__ argc; } ;
struct TYPE_4__ {int fetch_tags; struct refspec fetch; } ;
struct TYPE_3__ {int /*<<< orphan*/  exact_sha1; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 scalar_t__ TAGS_DEFAULT ; 
 scalar_t__ TAGS_SET ; 
 scalar_t__ TAGS_UNSET ; 
 int /*<<< orphan*/  TRANS_OPT_FOLLOWTAGS ; 
 int /*<<< orphan*/  append ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  backfill_tags (struct transport*,struct ref*) ; 
 int /*<<< orphan*/  check_not_current_branch (struct ref*) ; 
 scalar_t__ consume_refs (struct transport*,struct ref*) ; 
 int /*<<< orphan*/  dry_run ; 
 scalar_t__ fetch_refs (struct transport*,struct ref*) ; 
 int /*<<< orphan*/  find_non_local_tags (struct ref const*,struct ref**,struct ref***) ; 
 int /*<<< orphan*/  free_refs (struct ref*) ; 
 struct ref* get_ref_map (TYPE_2__*,struct ref const*,struct refspec*,scalar_t__,int*) ; 
 scalar_t__ prune ; 
 int /*<<< orphan*/  prune_refs (struct refspec*,struct ref*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refspec_ref_prefixes (struct refspec*,struct argv_array*) ; 
 scalar_t__ tags ; 
 struct ref* transport_get_remote_refs (struct transport*,struct argv_array*) ; 
 int /*<<< orphan*/  transport_set_option (struct transport*,int /*<<< orphan*/ ,char*) ; 
 int truncate_fetch_head () ; 
 int /*<<< orphan*/  update_head_ok ; 

__attribute__((used)) static int do_fetch(struct transport *transport,
		    struct refspec *rs)
{
	struct ref *ref_map;
	int autotags = (transport->remote->fetch_tags == 1);
	int retcode = 0;
	const struct ref *remote_refs;
	struct argv_array ref_prefixes = ARGV_ARRAY_INIT;
	int must_list_refs = 1;

	if (tags == TAGS_DEFAULT) {
		if (transport->remote->fetch_tags == 2)
			tags = TAGS_SET;
		if (transport->remote->fetch_tags == -1)
			tags = TAGS_UNSET;
	}

	/* if not appending, truncate FETCH_HEAD */
	if (!append && !dry_run) {
		retcode = truncate_fetch_head();
		if (retcode)
			goto cleanup;
	}

	if (rs->nr) {
		int i;

		refspec_ref_prefixes(rs, &ref_prefixes);

		/*
		 * We can avoid listing refs if all of them are exact
		 * OIDs
		 */
		must_list_refs = 0;
		for (i = 0; i < rs->nr; i++) {
			if (!rs->items[i].exact_sha1) {
				must_list_refs = 1;
				break;
			}
		}
	} else if (transport->remote && transport->remote->fetch.nr)
		refspec_ref_prefixes(&transport->remote->fetch, &ref_prefixes);

	if (tags == TAGS_SET || tags == TAGS_DEFAULT) {
		must_list_refs = 1;
		if (ref_prefixes.argc)
			argv_array_push(&ref_prefixes, "refs/tags/");
	}

	if (must_list_refs)
		remote_refs = transport_get_remote_refs(transport, &ref_prefixes);
	else
		remote_refs = NULL;

	argv_array_clear(&ref_prefixes);

	ref_map = get_ref_map(transport->remote, remote_refs, rs,
			      tags, &autotags);
	if (!update_head_ok)
		check_not_current_branch(ref_map);

	if (tags == TAGS_DEFAULT && autotags)
		transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, "1");
	if (prune) {
		/*
		 * We only prune based on refspecs specified
		 * explicitly (via command line or configuration); we
		 * don't care whether --tags was specified.
		 */
		if (rs->nr) {
			prune_refs(rs, ref_map, transport->url);
		} else {
			prune_refs(&transport->remote->fetch,
				   ref_map,
				   transport->url);
		}
	}
	if (fetch_refs(transport, ref_map) || consume_refs(transport, ref_map)) {
		free_refs(ref_map);
		retcode = 1;
		goto cleanup;
	}
	free_refs(ref_map);

	/* if neither --no-tags nor --tags was specified, do automated tag
	 * following ... */
	if (tags == TAGS_DEFAULT && autotags) {
		struct ref **tail = &ref_map;
		ref_map = NULL;
		find_non_local_tags(remote_refs, &ref_map, &tail);
		if (ref_map)
			backfill_tags(transport, ref_map);
		free_refs(ref_map);
	}

 cleanup:
	return retcode;
}