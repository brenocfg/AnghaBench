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
struct stored_bitmap {int dummy; } ;
struct rev_info {struct include_data* include_check_data; int /*<<< orphan*/  include_check; } ;
struct object_list {struct object_list* next; struct object* item; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; } ;
struct include_data {struct bitmap* seen; struct bitmap* base; struct bitmap_index* bitmap_git; } ;
struct ewah_bitmap {int dummy; } ;
struct bitmap_show_data {struct bitmap* base; struct bitmap_index* bitmap_git; } ;
struct bitmap_index {int /*<<< orphan*/  bitmaps; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int /*<<< orphan*/  SEEN ; 
 int /*<<< orphan*/  UNINTERESTING ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char*) ; 
 int /*<<< orphan*/  bitmap_get (struct bitmap*,int) ; 
 struct bitmap* bitmap_new () ; 
 int /*<<< orphan*/  bitmap_or_ewah (struct bitmap*,struct ewah_bitmap*) ; 
 int bitmap_position (struct bitmap_index*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct bitmap* ewah_to_bitmap (struct ewah_bitmap*) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_oid_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stored_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ewah_bitmap* lookup_stored_bitmap (struct stored_bitmap*) ; 
 int /*<<< orphan*/  object_list_insert (struct object*,struct object_list**) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  should_include ; 
 int /*<<< orphan*/  show_commit ; 
 int /*<<< orphan*/  show_object ; 
 int /*<<< orphan*/  traverse_commit_list (struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bitmap_show_data*) ; 

__attribute__((used)) static struct bitmap *find_objects(struct bitmap_index *bitmap_git,
				   struct rev_info *revs,
				   struct object_list *roots,
				   struct bitmap *seen)
{
	struct bitmap *base = NULL;
	int needs_walk = 0;

	struct object_list *not_mapped = NULL;

	/*
	 * Go through all the roots for the walk. The ones that have bitmaps
	 * on the bitmap index will be `or`ed together to form an initial
	 * global reachability analysis.
	 *
	 * The ones without bitmaps in the index will be stored in the
	 * `not_mapped_list` for further processing.
	 */
	while (roots) {
		struct object *object = roots->item;
		roots = roots->next;

		if (object->type == OBJ_COMMIT) {
			khiter_t pos = kh_get_oid_map(bitmap_git->bitmaps, object->oid);

			if (pos < kh_end(bitmap_git->bitmaps)) {
				struct stored_bitmap *st = kh_value(bitmap_git->bitmaps, pos);
				struct ewah_bitmap *or_with = lookup_stored_bitmap(st);

				if (base == NULL)
					base = ewah_to_bitmap(or_with);
				else
					bitmap_or_ewah(base, or_with);

				object->flags |= SEEN;
				continue;
			}
		}

		object_list_insert(object, &not_mapped);
	}

	/*
	 * Best case scenario: We found bitmaps for all the roots,
	 * so the resulting `or` bitmap has the full reachability analysis
	 */
	if (not_mapped == NULL)
		return base;

	roots = not_mapped;

	/*
	 * Let's iterate through all the roots that don't have bitmaps to
	 * check if we can determine them to be reachable from the existing
	 * global bitmap.
	 *
	 * If we cannot find them in the existing global bitmap, we'll need
	 * to push them to an actual walk and run it until we can confirm
	 * they are reachable
	 */
	while (roots) {
		struct object *object = roots->item;
		int pos;

		roots = roots->next;
		pos = bitmap_position(bitmap_git, &object->oid);

		if (pos < 0 || base == NULL || !bitmap_get(base, pos)) {
			object->flags &= ~UNINTERESTING;
			add_pending_object(revs, object, "");
			needs_walk = 1;
		} else {
			object->flags |= SEEN;
		}
	}

	if (needs_walk) {
		struct include_data incdata;
		struct bitmap_show_data show_data;

		if (base == NULL)
			base = bitmap_new();

		incdata.bitmap_git = bitmap_git;
		incdata.base = base;
		incdata.seen = seen;

		revs->include_check = should_include;
		revs->include_check_data = &incdata;

		if (prepare_revision_walk(revs))
			die("revision walk setup failed");

		show_data.bitmap_git = bitmap_git;
		show_data.base = base;

		traverse_commit_list(revs, show_commit, show_object,
				     &show_data);
	}

	return base;
}