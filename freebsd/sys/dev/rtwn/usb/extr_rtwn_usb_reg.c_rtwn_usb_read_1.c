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
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ rtwn_usb_read_region_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int*,int) ; 

uint8_t
rtwn_usb_read_1(struct rtwn_softc *sc, uint16_t addr)
{
	uint8_t val;

	if (rtwn_usb_read_region_1(sc, addr, &val, 1) != 0)
		return (0xff);
	return (val);
}