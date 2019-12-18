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
 int /*<<< orphan*/  write_c0_perfcnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_perfctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_counters(void *arg)
{
	write_c0_perfctrl(0);
	write_c0_perfcnt(0);
}