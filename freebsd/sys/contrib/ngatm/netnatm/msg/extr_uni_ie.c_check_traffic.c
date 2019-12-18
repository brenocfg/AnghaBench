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
typedef  scalar_t__ u_int ;
struct tallow {scalar_t__ mask; scalar_t__ mopt_flag; scalar_t__ mopt_mask; scalar_t__ mopt_val; } ;

/* Variables and functions */

__attribute__((used)) static int
check_traffic(u_int mask, u_int mopt, struct tallow *a)
{
	if(mask != a->mask)
		return 0;

	if(a->mopt_flag == 0) {
		/* not allowed */
		if(mopt == 0xffff)
			return 1;
		return 0;
	}

	if(a->mopt_flag < 0) {
		/* optional */
		if(mopt == 0xffff)
			return 1;
		if((mopt & a->mopt_mask) == a->mopt_val)
			return 1;
		return 0;
	}
	
	/* required */
	if(mopt == 0xffff)
		return 0;
	if((mopt & a->mopt_mask) == a->mopt_val)
		return 1;
	return 0;
}