#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct refspec {int nr; TYPE_2__* items; } ;
struct remote {int /*<<< orphan*/  name; struct refspec fetch; } ;
struct object_id {int dummy; } ;
struct refname_hash_entry {struct object_id oid; } ;
typedef  struct ref {TYPE_1__* peer_ref; struct ref const* next; void* fetch_head_status; } const ref ;
struct hashmap {int dummy; } ;
struct branch {int /*<<< orphan*/  remote_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  pattern; scalar_t__* dst; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  old_oid; } ;

/* Variables and functions */
 void* FETCH_HEAD_IGNORE ; 
 void* FETCH_HEAD_MERGE ; 
 int TAGS_DEFAULT ; 
 int TAGS_SET ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_merge_config (struct ref const**,struct ref const*,struct branch*,struct ref const***) ; 
 int /*<<< orphan*/  add_one_refname ; 
 struct branch* branch_get (int /*<<< orphan*/ *) ; 
 int branch_has_merge_config (struct branch*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  find_non_local_tags (struct ref const*,struct ref const**,struct ref const***) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct hashmap*) ; 
 int /*<<< orphan*/  get_fetch_map (struct ref const*,TYPE_2__*,struct ref const***,int) ; 
 struct ref const* get_remote_ref (struct ref const*,char*) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 struct refname_hash_entry* hashmap_get_from_hash (struct hashmap*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 struct ref const* ref_remove_duplicates (struct ref const*) ; 
 struct refspec refmap ; 
 int /*<<< orphan*/  refname_hash_init (struct hashmap*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strhash (char const*) ; 
 TYPE_2__* tag_refspec ; 

__attribute__((used)) static struct ref *get_ref_map(struct remote *remote,
			       const struct ref *remote_refs,
			       struct refspec *rs,
			       int tags, int *autotags)
{
	int i;
	struct ref *rm;
	struct ref *ref_map = NULL;
	struct ref **tail = &ref_map;

	/* opportunistically-updated references: */
	struct ref *orefs = NULL, **oref_tail = &orefs;

	struct hashmap existing_refs;

	if (rs->nr) {
		struct refspec *fetch_refspec;

		for (i = 0; i < rs->nr; i++) {
			get_fetch_map(remote_refs, &rs->items[i], &tail, 0);
			if (rs->items[i].dst && rs->items[i].dst[0])
				*autotags = 1;
		}
		/* Merge everything on the command line (but not --tags) */
		for (rm = ref_map; rm; rm = rm->next)
			rm->fetch_head_status = FETCH_HEAD_MERGE;

		/*
		 * For any refs that we happen to be fetching via
		 * command-line arguments, the destination ref might
		 * have been missing or have been different than the
		 * remote-tracking ref that would be derived from the
		 * configured refspec.  In these cases, we want to
		 * take the opportunity to update their configured
		 * remote-tracking reference.  However, we do not want
		 * to mention these entries in FETCH_HEAD at all, as
		 * they would simply be duplicates of existing
		 * entries, so we set them FETCH_HEAD_IGNORE below.
		 *
		 * We compute these entries now, based only on the
		 * refspecs specified on the command line.  But we add
		 * them to the list following the refspecs resulting
		 * from the tags option so that one of the latter,
		 * which has FETCH_HEAD_NOT_FOR_MERGE, is not removed
		 * by ref_remove_duplicates() in favor of one of these
		 * opportunistic entries with FETCH_HEAD_IGNORE.
		 */
		if (refmap.nr)
			fetch_refspec = &refmap;
		else
			fetch_refspec = &remote->fetch;

		for (i = 0; i < fetch_refspec->nr; i++)
			get_fetch_map(ref_map, &fetch_refspec->items[i], &oref_tail, 1);
	} else if (refmap.nr) {
		die("--refmap option is only meaningful with command-line refspec(s).");
	} else {
		/* Use the defaults */
		struct branch *branch = branch_get(NULL);
		int has_merge = branch_has_merge_config(branch);
		if (remote &&
		    (remote->fetch.nr ||
		     /* Note: has_merge implies non-NULL branch->remote_name */
		     (has_merge && !strcmp(branch->remote_name, remote->name)))) {
			for (i = 0; i < remote->fetch.nr; i++) {
				get_fetch_map(remote_refs, &remote->fetch.items[i], &tail, 0);
				if (remote->fetch.items[i].dst &&
				    remote->fetch.items[i].dst[0])
					*autotags = 1;
				if (!i && !has_merge && ref_map &&
				    !remote->fetch.items[0].pattern)
					ref_map->fetch_head_status = FETCH_HEAD_MERGE;
			}
			/*
			 * if the remote we're fetching from is the same
			 * as given in branch.<name>.remote, we add the
			 * ref given in branch.<name>.merge, too.
			 *
			 * Note: has_merge implies non-NULL branch->remote_name
			 */
			if (has_merge &&
			    !strcmp(branch->remote_name, remote->name))
				add_merge_config(&ref_map, remote_refs, branch, &tail);
		} else {
			ref_map = get_remote_ref(remote_refs, "HEAD");
			if (!ref_map)
				die(_("Couldn't find remote ref HEAD"));
			ref_map->fetch_head_status = FETCH_HEAD_MERGE;
			tail = &ref_map->next;
		}
	}

	if (tags == TAGS_SET)
		/* also fetch all tags */
		get_fetch_map(remote_refs, tag_refspec, &tail, 0);
	else if (tags == TAGS_DEFAULT && *autotags)
		find_non_local_tags(remote_refs, &ref_map, &tail);

	/* Now append any refs to be updated opportunistically: */
	*tail = orefs;
	for (rm = orefs; rm; rm = rm->next) {
		rm->fetch_head_status = FETCH_HEAD_IGNORE;
		tail = &rm->next;
	}

	ref_map = ref_remove_duplicates(ref_map);

	refname_hash_init(&existing_refs);
	for_each_ref(add_one_refname, &existing_refs);

	for (rm = ref_map; rm; rm = rm->next) {
		if (rm->peer_ref) {
			const char *refname = rm->peer_ref->name;
			struct refname_hash_entry *peer_item;

			peer_item = hashmap_get_from_hash(&existing_refs,
							  strhash(refname),
							  refname);
			if (peer_item) {
				struct object_id *old_oid = &peer_item->oid;
				oidcpy(&rm->peer_ref->old_oid, old_oid);
			}
		}
	}
	hashmap_free(&existing_refs, 1);

	return ref_map;
}