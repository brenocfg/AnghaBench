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
struct TYPE_3__ {scalar_t__ cl_class; } ;
struct TYPE_4__ {TYPE_1__ mem_cons; int /*<<< orphan*/  mem_kbd; } ;

/* Variables and functions */
 scalar_t__ CL_DUPLEX ; 
 TYPE_2__* PAGE0 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pdc_cons ; 
 scalar_t__ pdc_console_initialized ; 
 int /*<<< orphan*/  register_console (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc_console_init_force(void)
{
	if (pdc_console_initialized)
		return;
	++pdc_console_initialized;
	
	/* If the console is duplex then copy the COUT parameters to CIN. */
	if (PAGE0->mem_cons.cl_class == CL_DUPLEX)
		memcpy(&PAGE0->mem_kbd, &PAGE0->mem_cons, sizeof(PAGE0->mem_cons));

	/* register the pdc console */
	register_console(&pdc_cons);
}