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
struct nae_port_config {scalar_t__ num_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_REG (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_setup_rx_base_config(uint64_t nae_base, int maxports,
    struct nae_port_config *cfg)
{
	int base = 0;
	uint32_t val;
	int i;
	int id;

	for (i = 0; i < (maxports/2); i++) {
		id = 0x12 + i; /* RX_IF_BASE_CONFIG0 */

		val = (base & 0x3ff);
		base += cfg[(i * 2)].num_channels;

		val |= ((base & 0x3ff) << 16);
		base += cfg[(i * 2) + 1].num_channels;

		nlm_write_nae_reg(nae_base, NAE_REG(7, 0, id), val);
	}
}