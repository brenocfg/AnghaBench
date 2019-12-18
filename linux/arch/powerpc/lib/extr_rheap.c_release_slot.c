#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  empty_slots; int /*<<< orphan*/  empty_list; } ;
typedef  TYPE_1__ rh_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ rh_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void release_slot(rh_info_t * info, rh_block_t * blk)
{
	list_add(&blk->list, &info->empty_list);
	info->empty_slots++;
}