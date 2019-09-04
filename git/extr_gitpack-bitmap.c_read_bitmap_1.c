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
struct ewah_bitmap {int dummy; } ;
struct bitmap_index {scalar_t__ map; scalar_t__ map_pos; scalar_t__ map_size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  ewah_pool_free (struct ewah_bitmap*) ; 
 struct ewah_bitmap* ewah_pool_new () ; 
 scalar_t__ ewah_read_mmap (struct ewah_bitmap*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct ewah_bitmap *read_bitmap_1(struct bitmap_index *index)
{
	struct ewah_bitmap *b = ewah_pool_new();

	ssize_t bitmap_size = ewah_read_mmap(b,
		index->map + index->map_pos,
		index->map_size - index->map_pos);

	if (bitmap_size < 0) {
		error("Failed to load bitmap index (corrupted?)");
		ewah_pool_free(b);
		return NULL;
	}

	index->map_pos += bitmap_size;
	return b;
}