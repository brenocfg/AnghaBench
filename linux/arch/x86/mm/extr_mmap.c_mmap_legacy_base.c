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

/* Variables and functions */
 unsigned long __TASK_UNMAPPED_BASE (unsigned long) ; 

__attribute__((used)) static unsigned long mmap_legacy_base(unsigned long rnd,
				      unsigned long task_size)
{
	return __TASK_UNMAPPED_BASE(task_size) + rnd;
}