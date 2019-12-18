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
typedef  scalar_t__ uint32_t ;
struct hhook_head {int hhh_flags; } ;

/* Variables and functions */
 int HHH_ISINVNET ; 
 scalar_t__ HHOOK_HEADISINVNET ; 

uint32_t
hhook_head_is_virtualised(struct hhook_head *hhh)
{
	uint32_t ret;

	ret = 0;

	if (hhh != NULL) {
		if (hhh->hhh_flags & HHH_ISINVNET)
			ret = HHOOK_HEADISINVNET;
	}

	return (ret);
}