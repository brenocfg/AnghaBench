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
struct cryp_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  sr; int /*<<< orphan*/  cr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_CRYPEN_DISABLE ; 
 int /*<<< orphan*/  CRYP_CR_FFLUSH_MASK ; 
 int /*<<< orphan*/  CRYP_SET_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CRYP_SR_INFIFO_READY_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cryp_activity (struct cryp_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cryp_wait_until_done (struct cryp_device_data*) ; 
 scalar_t__ readl_relaxed (int /*<<< orphan*/ *) ; 

void cryp_flush_inoutfifo(struct cryp_device_data *device_data)
{
	/*
	 * We always need to disable the hardware before trying to flush the
	 * FIFO. This is something that isn't written in the design
	 * specification, but we have been informed by the hardware designers
	 * that this must be done.
	 */
	cryp_activity(device_data, CRYP_CRYPEN_DISABLE);
	cryp_wait_until_done(device_data);

	CRYP_SET_BITS(&device_data->base->cr, CRYP_CR_FFLUSH_MASK);
	/*
	 * CRYP_SR_INFIFO_READY_MASK is the expected value on the status
	 * register when starting a new calculation, which means Input FIFO is
	 * not full and input FIFO is empty.
	 */
	while (readl_relaxed(&device_data->base->sr) !=
	       CRYP_SR_INFIFO_READY_MASK)
		cpu_relax();
}