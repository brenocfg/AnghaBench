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
struct AdapterControlBlock {int /*<<< orphan*/  qbuffer_lock; int /*<<< orphan*/  postDone_lock; int /*<<< orphan*/  srb_lock; int /*<<< orphan*/  isr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_INIT (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void arcmsr_mutex_init(struct AdapterControlBlock *acb)
{
	ARCMSR_LOCK_INIT(&acb->isr_lock, "arcmsr isr lock");
	ARCMSR_LOCK_INIT(&acb->srb_lock, "arcmsr srb lock");
	ARCMSR_LOCK_INIT(&acb->postDone_lock, "arcmsr postQ lock");
	ARCMSR_LOCK_INIT(&acb->qbuffer_lock, "arcmsr RW buffer lock");
}