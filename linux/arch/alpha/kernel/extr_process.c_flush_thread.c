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
struct TYPE_3__ {scalar_t__ unique; } ;
struct TYPE_4__ {TYPE_1__ pcb; scalar_t__ ieee_state; } ;

/* Variables and functions */
 int FPCR_DYN_NORMAL ; 
 TYPE_2__* current_thread_info () ; 
 int ieee_swcr_to_fpcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfpcr (int) ; 

void
flush_thread(void)
{
	/* Arrange for each exec'ed process to start off with a clean slate
	   with respect to the FPU.  This is all exceptions disabled.  */
	current_thread_info()->ieee_state = 0;
	wrfpcr(FPCR_DYN_NORMAL | ieee_swcr_to_fpcr(0));

	/* Clean slate for TLS.  */
	current_thread_info()->pcb.unique = 0;
}