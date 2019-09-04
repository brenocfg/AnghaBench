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
struct stored_bitmap {int dummy; } ;
struct TYPE_4__ {int nr; TYPE_1__* objects; } ;
struct rev_info {int tag_objects; int tree_objects; int blob_objects; TYPE_2__ pending; int /*<<< orphan*/  repo; } ;
struct object {int /*<<< orphan*/  oid; } ;
struct ewah_bitmap {scalar_t__ bit_size; } ;
struct bitmap_test_data {int /*<<< orphan*/  base; int /*<<< orphan*/  prg; scalar_t__ seen; struct bitmap_index* bitmap_git; } ;
struct bitmap_index {int version; int entry_count; int /*<<< orphan*/  bitmaps; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ khiter_t ;
struct TYPE_3__ {struct object* item; } ;

/* Variables and functions */
 scalar_t__ bitmap_equals (struct bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_new () ; 
 size_t bitmap_popcount (struct bitmap*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int ewah_checksum (struct ewah_bitmap*) ; 
 struct bitmap* ewah_to_bitmap (struct ewah_bitmap*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_bitmap_index (struct bitmap_index*) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_oid_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stored_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ewah_bitmap* lookup_stored_bitmap (struct stored_bitmap*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 struct bitmap_index* prepare_bitmap_git (int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  start_progress (char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_show_commit ; 
 int /*<<< orphan*/  test_show_object ; 
 int /*<<< orphan*/  traverse_commit_list (struct rev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bitmap_test_data*) ; 

void test_bitmap_walk(struct rev_info *revs)
{
	struct object *root;
	struct bitmap *result = NULL;
	khiter_t pos;
	size_t result_popcnt;
	struct bitmap_test_data tdata;
	struct bitmap_index *bitmap_git;

	if (!(bitmap_git = prepare_bitmap_git(revs->repo)))
		die("failed to load bitmap indexes");

	if (revs->pending.nr != 1)
		die("you must specify exactly one commit to test");

	fprintf(stderr, "Bitmap v%d test (%d entries loaded)\n",
		bitmap_git->version, bitmap_git->entry_count);

	root = revs->pending.objects[0].item;
	pos = kh_get_oid_map(bitmap_git->bitmaps, root->oid);

	if (pos < kh_end(bitmap_git->bitmaps)) {
		struct stored_bitmap *st = kh_value(bitmap_git->bitmaps, pos);
		struct ewah_bitmap *bm = lookup_stored_bitmap(st);

		fprintf(stderr, "Found bitmap for %s. %d bits / %08x checksum\n",
			oid_to_hex(&root->oid), (int)bm->bit_size, ewah_checksum(bm));

		result = ewah_to_bitmap(bm);
	}

	if (result == NULL)
		die("Commit %s doesn't have an indexed bitmap", oid_to_hex(&root->oid));

	revs->tag_objects = 1;
	revs->tree_objects = 1;
	revs->blob_objects = 1;

	result_popcnt = bitmap_popcount(result);

	if (prepare_revision_walk(revs))
		die("revision walk setup failed");

	tdata.bitmap_git = bitmap_git;
	tdata.base = bitmap_new();
	tdata.prg = start_progress("Verifying bitmap entries", result_popcnt);
	tdata.seen = 0;

	traverse_commit_list(revs, &test_show_commit, &test_show_object, &tdata);

	stop_progress(&tdata.prg);

	if (bitmap_equals(result, tdata.base))
		fprintf(stderr, "OK!\n");
	else
		fprintf(stderr, "Mismatch!\n");

	free_bitmap_index(bitmap_git);
}