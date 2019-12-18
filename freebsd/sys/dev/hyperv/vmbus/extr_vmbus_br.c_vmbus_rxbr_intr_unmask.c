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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmbus_rxbr {scalar_t__ rxbr_imask; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  vmbus_rxbr_avail (struct vmbus_rxbr*) ; 

uint32_t
vmbus_rxbr_intr_unmask(struct vmbus_rxbr *rbr)
{
	rbr->rxbr_imask = 0;
	mb();

	/*
	 * Now check to see if the ring buffer is still empty.
	 * If it is not, we raced and we need to process new
	 * incoming channel packets.
	 */
	return vmbus_rxbr_avail(rbr);
}