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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct muge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RX_ADDRH ; 
 int /*<<< orphan*/  ETH_RX_ADDRL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static int
lan78xx_setmacaddress(struct muge_softc *sc, const uint8_t *addr)
{
	int err;
	uint32_t val;

	muge_dbg_printf(sc,
	    "setting mac address to %02x:%02x:%02x:%02x:%02x:%02x\n",
	    addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	val = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	if ((err = lan78xx_write_reg(sc, ETH_RX_ADDRL, val)) != 0)
		goto done;

	val = (addr[5] << 8) | addr[4];
	err = lan78xx_write_reg(sc, ETH_RX_ADDRH, val);

done:
	return (err);
}