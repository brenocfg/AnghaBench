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
struct vmbus_rxbr {int rxbr_imask; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

void
vmbus_rxbr_intr_mask(struct vmbus_rxbr *rbr)
{
	rbr->rxbr_imask = 1;
	mb();
}