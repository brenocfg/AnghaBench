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
 int AAS_StartFrame (float) ; 
 int BLERR_LIBRARYNOTSETUP ; 
 int /*<<< orphan*/  BotLibSetup (char*) ; 

int Export_BotLibStartFrame(float time)
{
	if (!BotLibSetup("BotStartFrame")) return BLERR_LIBRARYNOTSETUP;
	return AAS_StartFrame(time);
}