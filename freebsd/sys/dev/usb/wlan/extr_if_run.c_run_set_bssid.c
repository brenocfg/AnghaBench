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
struct run_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_MAC_BSSID_DW0 ; 
 int /*<<< orphan*/  RT2860_MAC_BSSID_DW1 ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
run_set_bssid(struct run_softc *sc, const uint8_t *bssid)
{
	run_write(sc, RT2860_MAC_BSSID_DW0,
	    bssid[0] | bssid[1] << 8 | bssid[2] << 16 | bssid[3] << 24);
	run_write(sc, RT2860_MAC_BSSID_DW1,
	    bssid[4] | bssid[5] << 8);
}