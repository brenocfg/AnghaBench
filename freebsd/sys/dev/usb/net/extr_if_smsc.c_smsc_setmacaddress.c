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
struct smsc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC_MAC_ADDRH ; 
 int /*<<< orphan*/  SMSC_MAC_ADDRL ; 
 int /*<<< orphan*/  smsc_dbg_printf (struct smsc_softc*,char*,int const,int const,int const,int const,int const,int const) ; 
 int smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
smsc_setmacaddress(struct smsc_softc *sc, const uint8_t *addr)
{
	int err;
	uint32_t val;

	smsc_dbg_printf(sc, "setting mac address to %02x:%02x:%02x:%02x:%02x:%02x\n",
	                addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	val = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	if ((err = smsc_write_reg(sc, SMSC_MAC_ADDRL, val)) != 0)
		goto done;
		
	val = (addr[5] << 8) | addr[4];
	err = smsc_write_reg(sc, SMSC_MAC_ADDRH, val);
	
done:
	return (err);
}