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
struct zyd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_MAC_BSSADRH ; 
 int /*<<< orphan*/  ZYD_MAC_BSSADRL ; 
 int /*<<< orphan*/  zyd_write32_m (struct zyd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zyd_set_bssid(struct zyd_softc *sc, const uint8_t *addr)
{
	int error;
	uint32_t tmp;

	tmp = addr[3] << 24 | addr[2] << 16 | addr[1] << 8 | addr[0];
	zyd_write32_m(sc, ZYD_MAC_BSSADRL, tmp);
	tmp = addr[5] << 8 | addr[4];
	zyd_write32_m(sc, ZYD_MAC_BSSADRH, tmp);
fail:
	return (error);
}