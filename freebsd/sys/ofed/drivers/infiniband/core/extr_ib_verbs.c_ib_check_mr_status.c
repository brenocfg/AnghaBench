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
typedef  int /*<<< orphan*/  u32 ;
struct ib_mr_status {int dummy; } ;
struct ib_mr {TYPE_1__* device; } ;
struct TYPE_2__ {int (* check_mr_status ) (struct ib_mr*,int /*<<< orphan*/ ,struct ib_mr_status*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_mr*,int /*<<< orphan*/ ,struct ib_mr_status*) ; 

int ib_check_mr_status(struct ib_mr *mr, u32 check_mask,
		       struct ib_mr_status *mr_status)
{
	return mr->device->check_mr_status ?
		mr->device->check_mr_status(mr, check_mask, mr_status) : -ENOSYS;
}