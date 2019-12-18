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
struct sata_gemini {scalar_t__ muxmode; int /*<<< orphan*/  sata_bridge; } ;

/* Variables and functions */
 scalar_t__ GEMINI_MUXMODE_2 ; 
 scalar_t__ GEMINI_MUXMODE_3 ; 

bool gemini_sata_bridge_enabled(struct sata_gemini *sg, bool is_ata1)
{
	if (!sg->sata_bridge)
		return false;
	/*
	 * In muxmode 2 and 3 one of the ATA controllers is
	 * actually not connected to any SATA bridge.
	 */
	if ((sg->muxmode == GEMINI_MUXMODE_2) &&
	    !is_ata1)
		return false;
	if ((sg->muxmode == GEMINI_MUXMODE_3) &&
	    is_ata1)
		return false;

	return true;
}