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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_TX_CONFIG ; 
 int /*<<< orphan*/  NAE_TX_IORCRDT_INIT ; 
 int TXINITIORCR (int) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nlm_nae_set_ior_credit(uint64_t nae_base, uint32_t ifmask, uint32_t valmask)
{
	uint32_t tx_config, tx_ior_credit;

	tx_ior_credit = nlm_read_nae_reg(nae_base, NAE_TX_IORCRDT_INIT);
	tx_ior_credit &= ~ifmask;
	tx_ior_credit |= valmask;
	nlm_write_nae_reg(nae_base, NAE_TX_IORCRDT_INIT, tx_ior_credit);

	tx_config = nlm_read_nae_reg(nae_base, NAE_TX_CONFIG);
	/* need to toggle these bits for credits to be loaded */
	nlm_write_nae_reg(nae_base, NAE_TX_CONFIG,
	    tx_config | (TXINITIORCR(ifmask)));
	nlm_write_nae_reg(nae_base, NAE_TX_CONFIG,
	    tx_config & ~(TXINITIORCR(ifmask)));
}