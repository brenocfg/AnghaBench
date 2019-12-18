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
typedef  int /*<<< orphan*/  uint32_t ;
struct altera_sdcard_softc {int /*<<< orphan*/  as_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_OFF_CMD_ARG ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
altera_sdcard_write_cmd_arg(struct altera_sdcard_softc *sc, uint32_t cmd_arg)
{

	bus_write_4(sc->as_res, ALTERA_SDCARD_OFF_CMD_ARG, htole32(cmd_arg));
}