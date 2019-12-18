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
struct TYPE_2__ {int /*<<< orphan*/  num_boxes; } ;

/* Variables and functions */
 int /*<<< orphan*/  skx_count_chabox () ; 
 int /*<<< orphan*/  skx_msr_uncores ; 
 TYPE_1__ skx_uncore_chabox ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 

void skx_uncore_cpu_init(void)
{
	skx_uncore_chabox.num_boxes = skx_count_chabox();
	uncore_msr_uncores = skx_msr_uncores;
}