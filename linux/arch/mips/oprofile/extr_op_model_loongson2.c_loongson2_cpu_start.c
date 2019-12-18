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
struct TYPE_2__ {int /*<<< orphan*/  ctrl; scalar_t__ cnt2_enabled; scalar_t__ cnt1_enabled; } ;

/* Variables and functions */
 TYPE_1__ reg ; 
 int /*<<< orphan*/  write_c0_perfctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loongson2_cpu_start(void *args)
{
	/* Start all counters on current CPU */
	if (reg.cnt1_enabled || reg.cnt2_enabled)
		write_c0_perfctrl(reg.ctrl);
}