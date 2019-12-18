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
struct AdapterControlBlock {int /*<<< orphan*/  isr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arcmsr_interrupt (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_intr_handler(void *arg)
{
	struct AdapterControlBlock *acb = (struct AdapterControlBlock *)arg;

	ARCMSR_LOCK_ACQUIRE(&acb->isr_lock);
	arcmsr_interrupt(acb);
	ARCMSR_LOCK_RELEASE(&acb->isr_lock);
}