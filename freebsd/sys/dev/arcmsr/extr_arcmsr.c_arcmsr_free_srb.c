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
struct CommandControlBlock {scalar_t__ srb_flags; int /*<<< orphan*/  srb_state; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {size_t workingsrb_doneindex; int /*<<< orphan*/  srb_lock; struct CommandControlBlock** srbworkingQ; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 size_t ARCMSR_MAX_FREESRB_NUM ; 
 int /*<<< orphan*/  ARCMSR_SRB_DONE ; 

__attribute__((used)) static void arcmsr_free_srb(struct CommandControlBlock *srb)
{
	struct AdapterControlBlock	*acb;

	acb = srb->acb;
	ARCMSR_LOCK_ACQUIRE(&acb->srb_lock);
	srb->srb_state = ARCMSR_SRB_DONE;
	srb->srb_flags = 0;
	acb->srbworkingQ[acb->workingsrb_doneindex] = srb;
	acb->workingsrb_doneindex++;
	acb->workingsrb_doneindex %= ARCMSR_MAX_FREESRB_NUM;
	ARCMSR_LOCK_RELEASE(&acb->srb_lock);
}