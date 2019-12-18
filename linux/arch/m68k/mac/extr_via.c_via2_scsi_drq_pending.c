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

/* Variables and functions */
 int IRQ_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_MAC_SCSIDRQ ; 
 size_t gIFR ; 
 int* via2 ; 

int via2_scsi_drq_pending(void)
{
	return via2[gIFR] & (1 << IRQ_IDX(IRQ_MAC_SCSIDRQ));
}