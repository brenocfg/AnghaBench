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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_MAL0_CFG ; 
 int /*<<< orphan*/  EMAC_RESET ; 
 int MAL_RESET ; 
 int mfdcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdcr (int /*<<< orphan*/ ,int) ; 

void ibm4xx_quiesce_eth(u32 *emac0, u32 *emac1)
{
	/* Quiesce the MAL and EMAC(s) since PIBS/OpenBIOS don't
	 * do this for us
	 */
	if (emac0)
		*emac0 = EMAC_RESET;
	if (emac1)
		*emac1 = EMAC_RESET;

	mtdcr(DCRN_MAL0_CFG, MAL_RESET);
	while (mfdcr(DCRN_MAL0_CFG) & MAL_RESET)
		; /* loop until reset takes effect */
}