#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr; struct object_array_entry* objects; } ;
struct rev_info {int /*<<< orphan*/  repo; TYPE_1__ pending; } ;
struct object_id {int dummy; } ;
struct object_array_entry {char const* name; TYPE_3__* item; } ;
struct object {int flags; } ;
struct TYPE_6__ {int flags; scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_3__ object; } ;
struct TYPE_5__ {int hexsz; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int SHOWN ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char*) ; 
 int dwim_ref (char const*,int,struct object_id*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_tag_in_date_range (TYPE_3__*,struct rev_info*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 struct object* parse_object_or_die (struct object_id*,char*) ; 
 scalar_t__ read_ref_full (char const*,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int strlen (char const*) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_or_die (int,char const*,int) ; 

__attribute__((used)) static int write_bundle_refs(int bundle_fd, struct rev_info *revs)
{
	int i;
	int ref_count = 0;

	for (i = 0; i < revs->pending.nr; i++) {
		struct object_array_entry *e = revs->pending.objects + i;
		struct object_id oid;
		char *ref;
		const char *display_ref;
		int flag;

		if (e->item->flags & UNINTERESTING)
			continue;
		if (dwim_ref(e->name, strlen(e->name), &oid, &ref) != 1)
			goto skip_write_ref;
		if (read_ref_full(e->name, RESOLVE_REF_READING, &oid, &flag))
			flag = 0;
		display_ref = (flag & REF_ISSYMREF) ? e->name : ref;

		if (e->item->type == OBJ_TAG &&
				!is_tag_in_date_range(e->item, revs)) {
			e->item->flags |= UNINTERESTING;
			goto skip_write_ref;
		}

		/*
		 * Make sure the refs we wrote out is correct; --max-count and
		 * other limiting options could have prevented all the tips
		 * from getting output.
		 *
		 * Non commit objects such as tags and blobs do not have
		 * this issue as they are not affected by those extra
		 * constraints.
		 */
		if (!(e->item->flags & SHOWN) && e->item->type == OBJ_COMMIT) {
			warning(_("ref '%s' is excluded by the rev-list options"),
				e->name);
			goto skip_write_ref;
		}
		/*
		 * If you run "git bundle create bndl v1.0..v2.0", the
		 * name of the positive ref is "v2.0" but that is the
		 * commit that is referenced by the tag, and not the tag
		 * itself.
		 */
		if (!oideq(&oid, &e->item->oid)) {
			/*
			 * Is this the positive end of a range expressed
			 * in terms of a tag (e.g. v2.0 from the range
			 * "v1.0..v2.0")?
			 */
			struct commit *one = lookup_commit_reference(revs->repo, &oid);
			struct object *obj;

			if (e->item == &(one->object)) {
				/*
				 * Need to include e->name as an
				 * independent ref to the pack-objects
				 * input, so that the tag is included
				 * in the output; otherwise we would
				 * end up triggering "empty bundle"
				 * error.
				 */
				obj = parse_object_or_die(&oid, e->name);
				obj->flags |= SHOWN;
				add_pending_object(revs, obj, e->name);
			}
			goto skip_write_ref;
		}

		ref_count++;
		write_or_die(bundle_fd, oid_to_hex(&e->item->oid), the_hash_algo->hexsz);
		write_or_die(bundle_fd, " ", 1);
		write_or_die(bundle_fd, display_ref, strlen(display_ref));
		write_or_die(bundle_fd, "\n", 1);
 skip_write_ref:
		free(ref);
	}

	/* end header */
	write_or_die(bundle_fd, "\n", 1);
	return ref_count;
}