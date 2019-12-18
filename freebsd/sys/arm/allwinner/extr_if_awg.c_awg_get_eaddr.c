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
typedef  int u_char ;
struct awg_softc {int dummy; } ;
typedef  int /*<<< orphan*/  rootkey ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_SID_FUSE_ROOTKEY ; 
 int /*<<< orphan*/  EMAC_ADDR_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_ADDR_LOW (int /*<<< orphan*/ ) ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int arc4random () ; 
 scalar_t__ aw_sid_get_fuse (int /*<<< orphan*/ ,int*,int*) ; 
 struct awg_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
awg_get_eaddr(device_t dev, uint8_t *eaddr)
{
	struct awg_softc *sc;
	uint32_t maclo, machi, rnd;
	u_char rootkey[16];
	uint32_t rootkey_size;

	sc = device_get_softc(dev);

	machi = RD4(sc, EMAC_ADDR_HIGH(0)) & 0xffff;
	maclo = RD4(sc, EMAC_ADDR_LOW(0));

	rootkey_size = sizeof(rootkey);
	if (maclo == 0xffffffff && machi == 0xffff) {
		/* MAC address in hardware is invalid, create one */
		if (aw_sid_get_fuse(AW_SID_FUSE_ROOTKEY, rootkey,
		    &rootkey_size) == 0 &&
		    (rootkey[3] | rootkey[12] | rootkey[13] | rootkey[14] |
		     rootkey[15]) != 0) {
			/* MAC address is derived from the root key in SID */
			maclo = (rootkey[13] << 24) | (rootkey[12] << 16) |
				(rootkey[3] << 8) | 0x02;
			machi = (rootkey[15] << 8) | rootkey[14];
		} else {
			/* Create one */
			rnd = arc4random();
			maclo = 0x00f2 | (rnd & 0xffff0000);
			machi = rnd & 0xffff;
		}
	}

	eaddr[0] = maclo & 0xff;
	eaddr[1] = (maclo >> 8) & 0xff;
	eaddr[2] = (maclo >> 16) & 0xff;
	eaddr[3] = (maclo >> 24) & 0xff;
	eaddr[4] = machi & 0xff;
	eaddr[5] = (machi >> 8) & 0xff;
}