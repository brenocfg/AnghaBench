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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_edma3cc_param_set {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_EDMA3CC_OPT (unsigned int) ; 
 int /*<<< orphan*/  bus_write_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ti_edma3_sc ; 

void
ti_edma3_param_write(unsigned int ch, struct ti_edma3cc_param_set *prs)
{
	bus_write_region_4(ti_edma3_sc->mem_res[0], TI_EDMA3CC_OPT(ch),
	    (uint32_t *) prs, 8);
}