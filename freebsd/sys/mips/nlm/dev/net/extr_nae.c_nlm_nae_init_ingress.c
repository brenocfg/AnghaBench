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
 int /*<<< orphan*/  NAE_PARSER_CONFIG ; 
 int /*<<< orphan*/  NAE_RX_CONFIG ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_init_ingress(uint64_t nae_base, uint32_t desc_size)
{
	uint32_t rx_cfg;
	uint32_t parser_threshold = 384;

	rx_cfg = nlm_read_nae_reg(nae_base, NAE_RX_CONFIG);
	rx_cfg &= ~(0x3 << 1);		/* reset max message size */
	rx_cfg &= ~(0xff << 4);		/* clear freein desc cluster size */
	rx_cfg &= ~(0x3f << 24);	/* reset rx status mask */ /*XXX: why not 7f */

	rx_cfg |= 1;			/* rx enable */
	rx_cfg |= (0x0 << 1);		/* max message size */
	rx_cfg |= (0x43 & 0x7f) << 24;	/* rx status mask */
	rx_cfg |= ((desc_size / 64) & 0xff) << 4; /* freein desc cluster size */
	nlm_write_nae_reg(nae_base, NAE_RX_CONFIG, rx_cfg);
	nlm_write_nae_reg(nae_base, NAE_PARSER_CONFIG,
	    (parser_threshold & 0x3ff) |
	    (((parser_threshold / desc_size) + 1) & 0xff) << 12 |
	    (((parser_threshold / 64) % desc_size) & 0xff) << 20);

	/*nlm_write_nae_reg(nae_base, NAE_RX_FREE_FIFO_THRESH, 33);*/
}