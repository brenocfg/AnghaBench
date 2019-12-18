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
struct TYPE_2__ {struct bitmap_index* hashes; struct bitmap_index* objects; } ;
struct bitmap_index {int /*<<< orphan*/  haves; int /*<<< orphan*/  result; TYPE_1__ ext_index; int /*<<< orphan*/  bitmaps; int /*<<< orphan*/  tags; int /*<<< orphan*/  blobs; int /*<<< orphan*/  trees; int /*<<< orphan*/  commits; int /*<<< orphan*/  map_size; scalar_t__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewah_pool_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bitmap_index*) ; 
 int /*<<< orphan*/  kh_destroy_oid_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 

void free_bitmap_index(struct bitmap_index *b)
{
	if (!b)
		return;

	if (b->map)
		munmap(b->map, b->map_size);
	ewah_pool_free(b->commits);
	ewah_pool_free(b->trees);
	ewah_pool_free(b->blobs);
	ewah_pool_free(b->tags);
	kh_destroy_oid_map(b->bitmaps);
	free(b->ext_index.objects);
	free(b->ext_index.hashes);
	bitmap_free(b->result);
	bitmap_free(b->haves);
	free(b);
}