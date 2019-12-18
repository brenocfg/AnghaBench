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
struct TYPE_6__ {scalar_t__ pv_va; } ;
struct TYPE_5__ {scalar_t__ pv_va; } ;
struct TYPE_4__ {scalar_t__ pv_va; } ;

/* Variables and functions */
 int ABT_STACK_SIZE ; 
 int IRQ_STACK_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSR_ABT32_MODE ; 
 int /*<<< orphan*/  PSR_IRQ32_MODE ; 
 int /*<<< orphan*/  PSR_UND32_MODE ; 
 int UND_STACK_SIZE ; 
 TYPE_3__ abtstack ; 
 TYPE_2__ irqstack ; 
 int /*<<< orphan*/  set_stackptr (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ undstack ; 

void
set_stackptrs(int cpu)
{

	set_stackptr(PSR_IRQ32_MODE,
	    irqstack.pv_va + ((IRQ_STACK_SIZE * PAGE_SIZE) * (cpu + 1)));
	set_stackptr(PSR_ABT32_MODE,
	    abtstack.pv_va + ((ABT_STACK_SIZE * PAGE_SIZE) * (cpu + 1)));
	set_stackptr(PSR_UND32_MODE,
	    undstack.pv_va + ((UND_STACK_SIZE * PAGE_SIZE) * (cpu + 1)));
}