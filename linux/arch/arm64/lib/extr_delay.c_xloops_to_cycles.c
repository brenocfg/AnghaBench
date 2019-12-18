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
 unsigned long HZ ; 
 unsigned long loops_per_jiffy ; 

__attribute__((used)) static inline unsigned long xloops_to_cycles(unsigned long xloops)
{
	return (xloops * loops_per_jiffy * HZ) >> 32;
}