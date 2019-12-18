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
typedef  scalar_t__ u64 ;
struct TYPE_6__ {TYPE_2__* queue; } ;
struct cpt_vf {int /*<<< orphan*/  flags; TYPE_3__ cqinfo; } ;
struct TYPE_5__ {TYPE_1__* qhead; } ;
struct TYPE_4__ {scalar_t__ dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_FLAG_DEVICE_READY ; 
 int /*<<< orphan*/  CPT_TIMER_THOLD ; 
 int /*<<< orphan*/  cptvf_write_vq_ctl (struct cpt_vf*,int) ; 
 int /*<<< orphan*/  cptvf_write_vq_done_numwait (struct cpt_vf*,int) ; 
 int /*<<< orphan*/  cptvf_write_vq_done_timewait (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cptvf_write_vq_doorbell (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cptvf_write_vq_inprog (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cptvf_write_vq_saddr (struct cpt_vf*,scalar_t__) ; 

__attribute__((used)) static void cptvf_device_init(struct cpt_vf *cptvf)
{
	u64 base_addr = 0;

	/* Disable the VQ */
	cptvf_write_vq_ctl(cptvf, 0);
	/* Reset the doorbell */
	cptvf_write_vq_doorbell(cptvf, 0);
	/* Clear inflight */
	cptvf_write_vq_inprog(cptvf, 0);
	/* Write VQ SADDR */
	/* TODO: for now only one queue, so hard coded */
	base_addr = (u64)(cptvf->cqinfo.queue[0].qhead->dma_addr);
	cptvf_write_vq_saddr(cptvf, base_addr);
	/* Configure timerhold / coalescence */
	cptvf_write_vq_done_timewait(cptvf, CPT_TIMER_THOLD);
	cptvf_write_vq_done_numwait(cptvf, 1);
	/* Enable the VQ */
	cptvf_write_vq_ctl(cptvf, 1);
	/* Flag the VF ready */
	cptvf->flags |= CPT_FLAG_DEVICE_READY;
}