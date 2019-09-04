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
struct commit_list {TYPE_2__* item; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ DEBUG_BISECT ; 
 int TREESAME ; 
 int weight (struct commit_list*) ; 

__attribute__((used)) static inline int halfway(struct commit_list *p, int nr)
{
	/*
	 * Don't short-cut something we are not going to return!
	 */
	if (p->item->object.flags & TREESAME)
		return 0;
	if (DEBUG_BISECT)
		return 0;
	/*
	 * 2 and 3 are halfway of 5.
	 * 3 is halfway of 6 but 2 and 4 are not.
	 */
	switch (2 * weight(p) - nr) {
	case -1: case 0: case 1:
		return 1;
	default:
		return 0;
	}
}