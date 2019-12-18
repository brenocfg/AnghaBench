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
typedef  int uint32_t ;
struct thread {TYPE_1__* td_pcb; } ;
struct TYPE_2__ {int pcb_flags; } ;

/* Variables and functions */
 int PCB_CDSCR ; 
 int PCB_CFSCR ; 
 int /*<<< orphan*/  SPR_DSCRP ; 
 int /*<<< orphan*/  SPR_FSCR ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup_power_extras(struct thread *td)
{
	uint32_t pcb_flags;

	if (td != curthread)
		return;

	pcb_flags = td->td_pcb->pcb_flags;
	/* Clean up registers not managed by MSR. */
	if (pcb_flags & PCB_CFSCR)
		mtspr(SPR_FSCR, 0);
	if (pcb_flags & PCB_CDSCR) 
		mtspr(SPR_DSCRP, 0);
}