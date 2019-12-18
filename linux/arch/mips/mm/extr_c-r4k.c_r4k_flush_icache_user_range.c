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
 void __r4k_flush_icache_range (unsigned long,unsigned long,int) ; 

__attribute__((used)) static void r4k_flush_icache_user_range(unsigned long start, unsigned long end)
{
	return __r4k_flush_icache_range(start, end, true);
}