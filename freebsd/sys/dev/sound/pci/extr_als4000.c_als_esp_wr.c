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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_ESP_WR_DATA ; 
 int /*<<< orphan*/  ALS_ESP_WR_STATUS ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
als_esp_wr(struct sc_info *sc, u_int8_t data)
{
	u_int32_t	tries, v;

	tries = 1000;
	do {
		v = bus_space_read_1(sc->st, sc->sh, ALS_ESP_WR_STATUS);
		if (~v & 0x80)
			break;
		DELAY(20);
	} while (--tries != 0);

	if (tries == 0)
		device_printf(sc->dev, "als_esp_wr timeout");

	bus_space_write_1(sc->st, sc->sh, ALS_ESP_WR_DATA, data);
}