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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  char u_char ;
struct emac_softc {int dummy; } ;
typedef  int /*<<< orphan*/  rootkey ;

/* Variables and functions */
 int /*<<< orphan*/  AW_SID_FUSE_ROOTKEY ; 
 int /*<<< orphan*/  EMAC_MAC_A0 ; 
 int /*<<< orphan*/  EMAC_MAC_A1 ; 
 int EMAC_READ_REG (struct emac_softc*,int /*<<< orphan*/ ) ; 
 int arc4random () ; 
 scalar_t__ aw_sid_get_fuse (int /*<<< orphan*/ ,char*,size_t*) ; 
 scalar_t__ bootverbose ; 
 char* ether_sprintf (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
emac_get_hwaddr(struct emac_softc *sc, uint8_t *hwaddr)
{
	uint32_t val0, val1, rnd;
	u_char rootkey[16];
	size_t rootkey_size;

	/*
	 * Try to get MAC address from running hardware.
	 * If there is something non-zero there just use it.
	 *
	 * Otherwise set the address to a convenient locally assigned address,
	 * using the SID rootkey.
	 * This is was uboot does so we end up with the same mac as if uboot
	 * did set it.
	 * If we can't get the root key, generate a random one,
	 * 'bsd' + random 24 low-order bits. 'b' is 0x62, which has the locally
	 * assigned bit set, and the broadcast/multicast bit clear.
	 */
	val0 = EMAC_READ_REG(sc, EMAC_MAC_A0);
	val1 = EMAC_READ_REG(sc, EMAC_MAC_A1);
	if ((val0 | val1) != 0 && (val0 | val1) != 0xffffff) {
		hwaddr[0] = (val1 >> 16) & 0xff;
		hwaddr[1] = (val1 >> 8) & 0xff;
		hwaddr[2] = (val1 >> 0) & 0xff;
		hwaddr[3] = (val0 >> 16) & 0xff;
		hwaddr[4] = (val0 >> 8) & 0xff;
		hwaddr[5] = (val0 >> 0) & 0xff;
	} else {
		rootkey_size = sizeof(rootkey);
		if (aw_sid_get_fuse(AW_SID_FUSE_ROOTKEY, rootkey,
		    &rootkey_size) == 0) {
			hwaddr[0] = 0x2;
			hwaddr[1] = rootkey[3];
			hwaddr[2] = rootkey[12];
			hwaddr[3] = rootkey[13];
			hwaddr[4] = rootkey[14];
			hwaddr[5] = rootkey[15];
		}
		else {
			rnd = arc4random() & 0x00ffffff;
			hwaddr[0] = 'b';
			hwaddr[1] = 's';
			hwaddr[2] = 'd';
			hwaddr[3] = (rnd >> 16) & 0xff;
			hwaddr[4] = (rnd >> 8) & 0xff;
			hwaddr[5] = (rnd >> 0) & 0xff;
		}
	}
	if (bootverbose)
		printf("MAC address: %s\n", ether_sprintf(hwaddr));
}