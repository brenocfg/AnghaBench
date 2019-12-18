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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static __inline int
cvtrssi(uint8_t ssi)
{
	int rssi = (int) ssi + 8;
	/* XXX hack guess until we have a real noise floor */
	rssi = 2*(87 - rssi);	/* NB: .5 dBm units */
	return (rssi < 0 ? 0 : rssi > 127 ? 127 : rssi);
}