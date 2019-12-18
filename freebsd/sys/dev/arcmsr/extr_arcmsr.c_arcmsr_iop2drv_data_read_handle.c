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
struct AdapterControlBlock {scalar_t__ wqbuf_firstindex; scalar_t__ wqbuf_lastindex; int /*<<< orphan*/  qbuffer_lock; int /*<<< orphan*/  acb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_MESSAGE_WQBUFFER_CLEARED ; 
 int /*<<< orphan*/  ACB_F_MESSAGE_WQBUFFER_READ ; 
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arcmsr_Write_data_2iop_wqbuffer (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_iop2drv_data_read_handle(struct AdapterControlBlock *acb)
{
	ARCMSR_LOCK_ACQUIRE(&acb->qbuffer_lock);
	acb->acb_flags |= ACB_F_MESSAGE_WQBUFFER_READ;
	/*
	*****************************************************************
	**   check if there are any mail packages from user space program
	**   in my post bag, now is the time to send them into Areca's firmware
	*****************************************************************
	*/
	if(acb->wqbuf_firstindex != acb->wqbuf_lastindex) {
		arcmsr_Write_data_2iop_wqbuffer(acb);
	}
	if(acb->wqbuf_firstindex == acb->wqbuf_lastindex) {
		acb->acb_flags |= ACB_F_MESSAGE_WQBUFFER_CLEARED;
	}
	ARCMSR_LOCK_RELEASE(&acb->qbuffer_lock);
}