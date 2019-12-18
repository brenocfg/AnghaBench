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

/* Variables and functions */
 int FDR10 ; 
 char* dump_linkspeed_compat (int) ; 

char *dump_linkspeedext_compat(uint32_t espeed, uint32_t speed, uint32_t fdr10)
{
	switch (espeed) {
	case 0:
		if (fdr10 & FDR10)
			return ("FDR10");
		else
			return dump_linkspeed_compat(speed);
		break;
	case 1:
		return ("FDR");
		break;
	case 2:
		return ("EDR");
		break;
	}
	return ("???");
}