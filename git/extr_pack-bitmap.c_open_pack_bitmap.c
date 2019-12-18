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
struct repository {int dummy; } ;
struct packed_git {struct packed_git* next; } ;
struct bitmap_index {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct packed_git* get_all_packs (struct repository*) ; 
 scalar_t__ open_pack_bitmap_1 (struct bitmap_index*,struct packed_git*) ; 

__attribute__((used)) static int open_pack_bitmap(struct repository *r,
			    struct bitmap_index *bitmap_git)
{
	struct packed_git *p;
	int ret = -1;

	assert(!bitmap_git->map);

	for (p = get_all_packs(r); p; p = p->next) {
		if (open_pack_bitmap_1(bitmap_git, p) == 0)
			ret = 0;
	}

	return ret;
}