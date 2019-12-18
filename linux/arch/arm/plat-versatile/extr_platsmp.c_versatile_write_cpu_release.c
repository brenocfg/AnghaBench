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
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sync_cache_w (int*) ; 
 int versatile_cpu_release ; 

__attribute__((used)) static void versatile_write_cpu_release(int val)
{
	versatile_cpu_release = val;
	smp_wmb();
	sync_cache_w(&versatile_cpu_release);
}