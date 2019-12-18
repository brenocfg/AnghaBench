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
typedef  int uint32_t ;
struct nvme_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCIEM_LINK_STA_SPEED ; 
 int PCIEM_LINK_STA_WIDTH ; 
 int /*<<< orphan*/  PCIER_LINK_STA ; 
 int nitems (int*) ; 
 int pcie_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
nvme_link_kBps(struct nvme_controller *ctrlr)
{
	uint32_t speed, lanes, link[] = { 1, 250000, 500000, 985000, 1970000 };
	uint32_t status;

	status = pcie_read_config(ctrlr->dev, PCIER_LINK_STA, 2);
	speed = status & PCIEM_LINK_STA_SPEED;
	lanes = (status & PCIEM_LINK_STA_WIDTH) >> 4;
	/*
	 * Failsafe on link speed indicator. If it is insane report the number of
	 * lanes as the speed. Not 100% accurate, but may be diagnostic.
	 */
	if (speed >= nitems(link))
		speed = 0;
	return link[speed] * lanes;
}