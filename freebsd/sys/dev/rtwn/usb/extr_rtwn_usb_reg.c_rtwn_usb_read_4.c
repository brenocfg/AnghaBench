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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int le32toh (int) ; 
 scalar_t__ rtwn_usb_read_region_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

uint32_t
rtwn_usb_read_4(struct rtwn_softc *sc, uint16_t addr)
{
	uint32_t val;

	if (rtwn_usb_read_region_1(sc, addr, (uint8_t *)&val, 4) != 0)
		return (0xffffffff);
	return (le32toh(val));
}