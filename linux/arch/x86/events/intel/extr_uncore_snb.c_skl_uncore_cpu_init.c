#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ x86_max_cores; } ;
struct TYPE_5__ {scalar_t__ num_boxes; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 TYPE_3__ boot_cpu_data ; 
 int /*<<< orphan*/  skl_msr_uncores ; 
 TYPE_2__ skl_uncore_cbox ; 
 int /*<<< orphan*/  skl_uncore_msr_ops ; 
 TYPE_1__ snb_uncore_arb ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 

void skl_uncore_cpu_init(void)
{
	uncore_msr_uncores = skl_msr_uncores;
	if (skl_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		skl_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	snb_uncore_arb.ops = &skl_uncore_msr_ops;
}