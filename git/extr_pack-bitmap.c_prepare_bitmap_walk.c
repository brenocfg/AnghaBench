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
struct tag {int dummy; } ;
struct TYPE_4__ {unsigned int nr; TYPE_1__* objects; } ;
struct rev_info {int ignore_missing_links; TYPE_2__ pending; int /*<<< orphan*/  repo; } ;
struct object_list {int dummy; } ;
struct object {scalar_t__ type; int flags; int /*<<< orphan*/  oid; } ;
struct bitmap_index {struct bitmap* haves; struct bitmap* result; } ;
struct bitmap {int dummy; } ;
struct TYPE_3__ {struct object* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ OBJ_NONE ; 
 scalar_t__ OBJ_TAG ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  bitmap_and_not (struct bitmap*,struct bitmap*) ; 
 struct bitmap* find_objects (struct bitmap_index*,struct rev_info*,struct object_list*,struct bitmap*) ; 
 int /*<<< orphan*/  free_bitmap_index (struct bitmap_index*) ; 
 int /*<<< orphan*/ * get_tagged_oid (struct tag*) ; 
 int /*<<< orphan*/  in_bitmapped_pack (struct bitmap_index*,struct object_list*) ; 
 scalar_t__ load_pack_bitmap (struct bitmap_index*) ; 
 int /*<<< orphan*/  object_array_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  object_list_insert (struct object*,struct object_list**) ; 
 scalar_t__ open_pack_bitmap (int /*<<< orphan*/ ,struct bitmap_index*) ; 
 struct object* parse_object_or_die (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_revision_walk () ; 
 struct bitmap_index* xcalloc (int,int) ; 

struct bitmap_index *prepare_bitmap_walk(struct rev_info *revs)
{
	unsigned int i;

	struct object_list *wants = NULL;
	struct object_list *haves = NULL;

	struct bitmap *wants_bitmap = NULL;
	struct bitmap *haves_bitmap = NULL;

	struct bitmap_index *bitmap_git = xcalloc(1, sizeof(*bitmap_git));
	/* try to open a bitmapped pack, but don't parse it yet
	 * because we may not need to use it */
	if (open_pack_bitmap(revs->repo, bitmap_git) < 0)
		goto cleanup;

	for (i = 0; i < revs->pending.nr; ++i) {
		struct object *object = revs->pending.objects[i].item;

		if (object->type == OBJ_NONE)
			parse_object_or_die(&object->oid, NULL);

		while (object->type == OBJ_TAG) {
			struct tag *tag = (struct tag *) object;

			if (object->flags & UNINTERESTING)
				object_list_insert(object, &haves);
			else
				object_list_insert(object, &wants);

			object = parse_object_or_die(get_tagged_oid(tag), NULL);
		}

		if (object->flags & UNINTERESTING)
			object_list_insert(object, &haves);
		else
			object_list_insert(object, &wants);
	}

	/*
	 * if we have a HAVES list, but none of those haves is contained
	 * in the packfile that has a bitmap, we don't have anything to
	 * optimize here
	 */
	if (haves && !in_bitmapped_pack(bitmap_git, haves))
		goto cleanup;

	/* if we don't want anything, we're done here */
	if (!wants)
		goto cleanup;

	/*
	 * now we're going to use bitmaps, so load the actual bitmap entries
	 * from disk. this is the point of no return; after this the rev_list
	 * becomes invalidated and we must perform the revwalk through bitmaps
	 */
	if (load_pack_bitmap(bitmap_git) < 0)
		goto cleanup;

	object_array_clear(&revs->pending);

	if (haves) {
		revs->ignore_missing_links = 1;
		haves_bitmap = find_objects(bitmap_git, revs, haves, NULL);
		reset_revision_walk();
		revs->ignore_missing_links = 0;

		if (haves_bitmap == NULL)
			BUG("failed to perform bitmap walk");
	}

	wants_bitmap = find_objects(bitmap_git, revs, wants, haves_bitmap);

	if (!wants_bitmap)
		BUG("failed to perform bitmap walk");

	if (haves_bitmap)
		bitmap_and_not(wants_bitmap, haves_bitmap);

	bitmap_git->result = wants_bitmap;
	bitmap_git->haves = haves_bitmap;

	return bitmap_git;

cleanup:
	free_bitmap_index(bitmap_git);
	return NULL;
}