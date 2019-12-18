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
struct thread_info {int slb_preload_tail; int /*<<< orphan*/  slb_preload_nr; } ;

/* Variables and functions */
 int SLB_PRELOAD_NR ; 

__attribute__((used)) static void preload_age(struct thread_info *ti)
{
	if (!ti->slb_preload_nr)
		return;
	ti->slb_preload_nr--;
	ti->slb_preload_tail = (ti->slb_preload_tail + 1) % SLB_PRELOAD_NR;
}