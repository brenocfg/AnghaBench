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
 int /*<<< orphan*/  nlm_is_xlp8xx_ax () ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_init_egress(uint64_t nae_base)
{
	uint32_t tx_cfg;

	tx_cfg = nlm_read_nae_reg(nae_base, NAE_TX_CONFIG);
	if (!nlm_is_xlp8xx_ax()) {
		nlm_write_nae_reg(nae_base, NAE_TX_CONFIG,
		    tx_cfg	|
		    0x1		|	/* tx enable */
		    0x2		|	/* tx ace */
		    0x4		|	/* tx compatible */
		    (1 << 3));
	} else {
		nlm_write_nae_reg(nae_base, NAE_TX_CONFIG,
		    tx_cfg	|
		    0x1		|	/* tx enable */
		    0x2);		/* tx ace */
	}
}