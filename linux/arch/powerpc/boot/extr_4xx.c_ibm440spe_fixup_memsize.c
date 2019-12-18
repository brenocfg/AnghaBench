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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_MQ0_B0BAS ; 
 int /*<<< orphan*/  DCRN_MQ0_B1BAS ; 
 int /*<<< orphan*/  DCRN_MQ0_B2BAS ; 
 int /*<<< orphan*/  DCRN_MQ0_B3BAS ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ibm440spe_decode_bas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfdcr (int /*<<< orphan*/ ) ; 

void ibm440spe_fixup_memsize(void)
{
	u64 banktop, memsize = 0;

	/* Ultimately, we should directly construct the memory node
	 * so we are able to handle holes in the memory address space
	 */
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B0BAS));
	if (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B1BAS));
	if (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B2BAS));
	if (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B3BAS));
	if (banktop > memsize)
		memsize = banktop;

	dt_fixup_memory(0, memsize);
}