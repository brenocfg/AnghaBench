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
 int /*<<< orphan*/  SATA_PHY_ASIC_STAT ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_cr_ack(void)
{
	while ((readl(SATA_PHY_ASIC_STAT) >> 16) & 0x1f)
		/* wait for an ack bit to be set */;
}