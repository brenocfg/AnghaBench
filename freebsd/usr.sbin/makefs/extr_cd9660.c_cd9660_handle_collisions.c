#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iso9660_disk ;
struct TYPE_13__ {TYPE_1__* isoDirRecord; int /*<<< orphan*/  cn_children; } ;
typedef  TYPE_2__ cd9660node ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_PREV (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_children_head ; 
 int cd9660_count_collisions (TYPE_2__*) ; 
 TYPE_2__* cd9660_rename_filename (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  cn_next_child ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cd9660_handle_collisions(iso9660_disk *diskStructure, cd9660node *colliding,
    int past)
{
	cd9660node *iter, *next, *prev;
	int skip;
	int delete_chars = 0;
	int temp_past = past;
	int temp_skip;
	int flag = 0;
	cd9660node *end_of_range;

	for (iter = TAILQ_FIRST(&colliding->cn_children);
	     iter != NULL && (next = TAILQ_NEXT(iter, cn_next_child)) != NULL;) {
		if (strcmp(iter->isoDirRecord->name,
		           next->isoDirRecord->name) != 0) {
			iter = TAILQ_NEXT(iter, cn_next_child);
			continue;
		}
		flag = 1;
		temp_skip = skip = cd9660_count_collisions(iter);
		end_of_range = iter;
		while (temp_skip > 0) {
			temp_skip--;
			end_of_range = TAILQ_NEXT(end_of_range, cn_next_child);
		}
		temp_past = past;
		while (temp_past > 0) {
			if ((next = TAILQ_NEXT(end_of_range, cn_next_child)) != NULL)
				end_of_range = next;
			else if ((prev = TAILQ_PREV(iter, cd9660_children_head, cn_next_child)) != NULL)
				iter = prev;
			else
				delete_chars++;
			temp_past--;
		}
		skip += past;
		iter = cd9660_rename_filename(diskStructure, iter, skip,
		    delete_chars);
	}
	return flag;
}