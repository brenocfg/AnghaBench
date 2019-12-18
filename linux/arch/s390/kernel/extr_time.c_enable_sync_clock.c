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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_sync_word ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_sync_clock(void)
{
	atomic_t *sw_ptr = this_cpu_ptr(&clock_sync_word);
	atomic_or(0x80000000, sw_ptr);
}