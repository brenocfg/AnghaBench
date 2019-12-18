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
struct bwi_rxbuf_hdr {int rxh_rssi; } ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
bwi_rf_calc_rssi_bcm2060(struct bwi_mac *mac, const struct bwi_rxbuf_hdr *hdr)
{
	int rssi;

	rssi = hdr->rxh_rssi;
	if (rssi > 127)
		rssi -= 256;
	return rssi;
}