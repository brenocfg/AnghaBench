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
typedef  int u32 ;

/* Variables and functions */
 int L3C_ELR_ERRSYN (int) ; 
 int L3C_ELR_ERRWAY (int) ; 
 int L3C_ESR_DATATAG_MASK ; 

__attribute__((used)) static bool xgene_edac_l3_promote_to_uc_err(u32 l3cesr, u32 l3celr)
{
	if (l3cesr & L3C_ESR_DATATAG_MASK) {
		switch (L3C_ELR_ERRSYN(l3celr)) {
		case 0x13C:
		case 0x0B4:
		case 0x007:
		case 0x00D:
		case 0x00E:
		case 0x019:
		case 0x01A:
		case 0x01C:
		case 0x04E:
		case 0x041:
			return true;
		}
	} else if (L3C_ELR_ERRWAY(l3celr) == 9)
		return true;

	return false;
}