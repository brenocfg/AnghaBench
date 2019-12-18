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
struct rum_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2573_MAC_CSR4 ; 
 int /*<<< orphan*/  RT2573_MAC_CSR5 ; 
 int const RT2573_NUM_BSSID_MSK (int) ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
rum_set_bssid(struct rum_softc *sc, const uint8_t *bssid)
{

	rum_write(sc, RT2573_MAC_CSR4,
	    bssid[0] | bssid[1] << 8 | bssid[2] << 16 | bssid[3] << 24);
	rum_write(sc, RT2573_MAC_CSR5,
	    bssid[4] | bssid[5] << 8 | RT2573_NUM_BSSID_MSK(1));
}