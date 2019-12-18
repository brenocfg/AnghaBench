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
struct rsu_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
rsu_hwrssi_to_rssi(struct rsu_softc *sc, int hw_rssi)
{
	int v;

	if (hw_rssi == 0)
		return (0);
	v = hw_rssi >> 4;
	if (v > 80)
		v = 80;
	return (v);
}