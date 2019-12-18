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
struct throtl_grp {int /*<<< orphan*/ * slice_start; } ;

/* Variables and functions */
 scalar_t__ throtl_slice_used (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  throtl_start_new_slice_with_credit (struct throtl_grp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_parent_slice_with_credit(struct throtl_grp *child_tg,
					struct throtl_grp *parent_tg, bool rw)
{
	if (throtl_slice_used(parent_tg, rw)) {
		throtl_start_new_slice_with_credit(parent_tg, rw,
				child_tg->slice_start[rw]);
	}

}