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
 int /*<<< orphan*/  XAUI_MAX_FRAME_LEN (int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_config_xaui_mtu(uint64_t nae_base, int nblock,
    int max_tx_frame_sz, int max_rx_frame_sz)
{
	uint32_t tx_words = max_tx_frame_sz >> 2; /* max_tx_frame_sz / 4 */

	/* write max frame length */
	nlm_write_nae_reg(nae_base,
	    XAUI_MAX_FRAME_LEN(nblock),
	    ((tx_words & 0x3ff) << 16) | (max_rx_frame_sz & 0xffff));
}