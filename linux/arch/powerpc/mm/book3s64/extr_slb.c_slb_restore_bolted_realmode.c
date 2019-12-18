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
struct TYPE_2__ {unsigned int slb_kern_bitmap; unsigned int slb_used_bitmap; scalar_t__ slb_cache_ptr; } ;

/* Variables and functions */
 unsigned int SLB_NUM_BOLTED ; 
 int /*<<< orphan*/  __slb_restore_bolted_realmode () ; 
 TYPE_1__* get_paca () ; 

void slb_restore_bolted_realmode(void)
{
	__slb_restore_bolted_realmode();
	get_paca()->slb_cache_ptr = 0;

	get_paca()->slb_kern_bitmap = (1U << SLB_NUM_BOLTED) - 1;
	get_paca()->slb_used_bitmap = get_paca()->slb_kern_bitmap;
}