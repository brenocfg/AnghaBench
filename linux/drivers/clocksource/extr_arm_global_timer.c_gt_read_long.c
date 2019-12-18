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
 scalar_t__ GT_COUNTER0 ; 
 scalar_t__ gt_base ; 
 unsigned long readl_relaxed (scalar_t__) ; 

__attribute__((used)) static unsigned long gt_read_long(void)
{
	return readl_relaxed(gt_base + GT_COUNTER0);
}