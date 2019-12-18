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
typedef  int uint16_t ;
struct ural_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int const*,char*) ; 
 int /*<<< orphan*/  RAL_MAC_CSR5 ; 
 int /*<<< orphan*/  RAL_MAC_CSR6 ; 
 int /*<<< orphan*/  RAL_MAC_CSR7 ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_set_bssid(struct ural_softc *sc, const uint8_t *bssid)
{
	uint16_t tmp;

	tmp = bssid[0] | bssid[1] << 8;
	ural_write(sc, RAL_MAC_CSR5, tmp);

	tmp = bssid[2] | bssid[3] << 8;
	ural_write(sc, RAL_MAC_CSR6, tmp);

	tmp = bssid[4] | bssid[5] << 8;
	ural_write(sc, RAL_MAC_CSR7, tmp);

	DPRINTF("setting BSSID to %6D\n", bssid, ":");
}