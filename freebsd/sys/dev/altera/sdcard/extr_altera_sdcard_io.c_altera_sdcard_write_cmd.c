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
typedef  int /*<<< orphan*/  uint16_t ;
struct altera_sdcard_softc {int /*<<< orphan*/  as_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_CMD ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
altera_sdcard_write_cmd(struct altera_sdcard_softc *sc, uint16_t cmd)
{

	bus_write_2(sc->as_res, ALTERA_SDCARD_OFF_CMD, htole16(cmd));
}