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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int rtwn_usb_write_region_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
rtwn_usb_write_4(struct rtwn_softc *sc, uint16_t addr, uint32_t val)
{
	val = htole32(val);
	return (rtwn_usb_write_region_1(sc, addr, (uint8_t *)&val, sizeof(val)));
}