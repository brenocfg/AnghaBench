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
struct cam_sim {int dummy; } ;
struct AdapterControlBlock {int /*<<< orphan*/  isr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arcmsr_interrupt (struct AdapterControlBlock*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arcmsr_poll(struct cam_sim *psim)
{
	struct AdapterControlBlock *acb;
	int	mutex;

	acb = (struct AdapterControlBlock *)cam_sim_softc(psim);
	mutex = mtx_owned(&acb->isr_lock);
	if( mutex == 0 )
		ARCMSR_LOCK_ACQUIRE(&acb->isr_lock);
	arcmsr_interrupt(acb);
	if( mutex == 0 )
		ARCMSR_LOCK_RELEASE(&acb->isr_lock);
}