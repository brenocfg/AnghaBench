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
struct AdapterControlBlock {int /*<<< orphan*/  isr_lock; int /*<<< orphan*/  srb_lock; int /*<<< orphan*/  postDone_lock; int /*<<< orphan*/  qbuffer_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_DESTROY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arcmsr_mutex_destroy(struct AdapterControlBlock *acb)
{
	ARCMSR_LOCK_DESTROY(&acb->qbuffer_lock);
	ARCMSR_LOCK_DESTROY(&acb->postDone_lock);
	ARCMSR_LOCK_DESTROY(&acb->srb_lock);
	ARCMSR_LOCK_DESTROY(&acb->isr_lock);
}