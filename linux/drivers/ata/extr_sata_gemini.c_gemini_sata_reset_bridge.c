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
struct sata_gemini {int /*<<< orphan*/  sata1_reset; int /*<<< orphan*/  sata0_reset; } ;

/* Variables and functions */
 int gemini_sata_setup_bridge (struct sata_gemini*,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reset_control_reset (int /*<<< orphan*/ ) ; 

int gemini_sata_reset_bridge(struct sata_gemini *sg,
			     unsigned int bridge)
{
	if (bridge == 0)
		reset_control_reset(sg->sata0_reset);
	else
		reset_control_reset(sg->sata1_reset);
	msleep(10);
	return gemini_sata_setup_bridge(sg, bridge);
}