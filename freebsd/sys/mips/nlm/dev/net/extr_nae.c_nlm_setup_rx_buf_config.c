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
struct nae_port_config {scalar_t__ type; int num_channels; int rxbuf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_RXBUF_BASE_DPTH ; 
 int /*<<< orphan*/  NAE_RXBUF_BASE_DPTH_ADDR ; 
 scalar_t__ UNKNOWN ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_setup_rx_buf_config(uint64_t nae_base, int maxports,
    struct nae_port_config *cfg)
{
	uint32_t val;
	int i, sz, k;
	int context = 0;
	int base = 0;

	for (i = 0; i < maxports; i++) {
		if (cfg[i].type == UNKNOWN)
			continue;
		for (k = 0; k < cfg[i].num_channels; k++) {
			/* write index (context num) */
			nlm_write_nae_reg(nae_base, NAE_RXBUF_BASE_DPTH_ADDR,
			    (context+k));

			/* write value (rx buf sizes) */
			sz = cfg[i].rxbuf_size;
			val = 0x80000000 | ((base << 2) & 0x3fff); /* base */
			val |= (((sz << 2)  & 0x3fff) << 16); /* size */

			nlm_write_nae_reg(nae_base, NAE_RXBUF_BASE_DPTH, val);
			nlm_write_nae_reg(nae_base, NAE_RXBUF_BASE_DPTH,
			    (0x7fffffff & val));
			base += sz;
		}
		context += cfg[i].num_channels;
	}
}