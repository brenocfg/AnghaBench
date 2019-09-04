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
struct refspec_item {char* src; scalar_t__ force; int /*<<< orphan*/  dst; scalar_t__ exact_sha1; scalar_t__ pattern; } ;
struct ref {int exact_oid; int force; struct ref* next; struct ref* peer_ref; int /*<<< orphan*/  name; int /*<<< orphan*/  old_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct ref* alloc_ref (char const*) ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 struct ref* get_expanded_map (struct ref const*,struct refspec_item const*) ; 
 struct ref* get_local_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid_hex (char const*,int /*<<< orphan*/ *) ; 
 struct ref* get_remote_ref (struct ref const*,char const*) ; 
 int /*<<< orphan*/  starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tail_link_ref (struct ref*,struct ref***) ; 

int get_fetch_map(const struct ref *remote_refs,
		  const struct refspec_item *refspec,
		  struct ref ***tail,
		  int missing_ok)
{
	struct ref *ref_map, **rmp;

	if (refspec->pattern) {
		ref_map = get_expanded_map(remote_refs, refspec);
	} else {
		const char *name = refspec->src[0] ? refspec->src : "HEAD";

		if (refspec->exact_sha1) {
			ref_map = alloc_ref(name);
			get_oid_hex(name, &ref_map->old_oid);
			ref_map->exact_oid = 1;
		} else {
			ref_map = get_remote_ref(remote_refs, name);
		}
		if (!missing_ok && !ref_map)
			die(_("couldn't find remote ref %s"), name);
		if (ref_map) {
			ref_map->peer_ref = get_local_ref(refspec->dst);
			if (ref_map->peer_ref && refspec->force)
				ref_map->peer_ref->force = 1;
		}
	}

	for (rmp = &ref_map; *rmp; ) {
		if ((*rmp)->peer_ref) {
			if (!starts_with((*rmp)->peer_ref->name, "refs/") ||
			    check_refname_format((*rmp)->peer_ref->name, 0)) {
				struct ref *ignore = *rmp;
				error(_("* Ignoring funny ref '%s' locally"),
				      (*rmp)->peer_ref->name);
				*rmp = (*rmp)->next;
				free(ignore->peer_ref);
				free(ignore);
				continue;
			}
		}
		rmp = &((*rmp)->next);
	}

	if (ref_map)
		tail_link_ref(ref_map, tail);

	return 0;
}