#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  num_boxes; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  icl_get_cbox_num () ; 
 int /*<<< orphan*/  icl_msr_uncores ; 
 TYPE_2__ icl_uncore_cbox ; 
 int /*<<< orphan*/  skl_uncore_msr_ops ; 
 TYPE_1__ snb_uncore_arb ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 

void icl_uncore_cpu_init(void)
{
	uncore_msr_uncores = icl_msr_uncores;
	icl_uncore_cbox.num_boxes = icl_get_cbox_num();
	snb_uncore_arb.ops = &skl_uncore_msr_ops;
}