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
 int /*<<< orphan*/  MAC_CONF1 ; 
 int /*<<< orphan*/  MAC_CONF2 ; 
 int /*<<< orphan*/  NAE_REG (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGMII_MAX_FRAME (int,int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_configure_sgmii_interface(uint64_t nae_base, int block, int port,
    int mtu, int loopback)
{
	uint32_t data1, data2;

	/* Apply a soft reset */
	data1 = (0x1 << 31); /* soft reset */
	if (loopback)
		data1 |= (0x01 << 8);
	data1 |= (0x01 << 2); /* Rx enable */
	data1 |= 0x01; /* Tx enable */
	nlm_write_nae_reg(nae_base, NAE_REG(block, port, MAC_CONF1), data1);

	data2 = (0x7 << 12) | /* pre-amble length=7 */
	    (0x2 << 8) | /* byteMode */
	    0x1;         /* fullDuplex */
	nlm_write_nae_reg(nae_base, NAE_REG(block, port, MAC_CONF2), data2);

	/* Remove a soft reset */
	data1 &= ~(0x01 << 31);
	nlm_write_nae_reg(nae_base, NAE_REG(block, port, MAC_CONF1), data1);

	/* setup sgmii max frame length */
	nlm_write_nae_reg(nae_base, SGMII_MAX_FRAME(block, port), mtu);
}