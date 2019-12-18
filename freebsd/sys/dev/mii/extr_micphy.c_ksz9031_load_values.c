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
struct mii_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ9031_CLOCK_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031_CONTROL_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031_RX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031_TX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  ksz90x1_load_values (struct mii_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*,int,int,char*,int,int,char*,int,int) ; 

__attribute__((used)) static void
ksz9031_load_values(struct mii_softc *sc, phandle_t node)
{

	ksz90x1_load_values(sc, node, 2, MII_KSZ9031_CONTROL_PAD_SKEW,
	    "txen-skew-ps", 0xf, 0, "rxdv-skew-ps", 0xf, 4,
	    NULL, 0, 0, NULL, 0, 0);
	ksz90x1_load_values(sc, node, 2, MII_KSZ9031_RX_DATA_PAD_SKEW,
	    "rxd0-skew-ps", 0xf, 0, "rxd1-skew-ps", 0xf, 4,
	    "rxd2-skew-ps", 0xf, 8, "rxd3-skew-ps", 0xf, 12);
	ksz90x1_load_values(sc, node, 2, MII_KSZ9031_TX_DATA_PAD_SKEW,
	    "txd0-skew-ps", 0xf, 0, "txd1-skew-ps", 0xf, 4,
	    "txd2-skew-ps", 0xf, 8, "txd3-skew-ps", 0xf, 12);
	ksz90x1_load_values(sc, node, 2, MII_KSZ9031_CLOCK_PAD_SKEW,
	    "rxc-skew-ps", 0x1f, 0, "txc-skew-ps", 0x1f, 5,
	    NULL, 0, 0, NULL, 0, 0);
}