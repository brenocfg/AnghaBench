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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_ESP_RD_DATA ; 
 int /*<<< orphan*/  ALS_ESP_RD_STATUS8 ; 
 int /*<<< orphan*/  ALS_ESP_RST ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
als_esp_reset(struct sc_info *sc)
{
	u_int32_t	tries, u, v;

	bus_space_write_1(sc->st, sc->sh, ALS_ESP_RST, 1);
	DELAY(10);
	bus_space_write_1(sc->st, sc->sh, ALS_ESP_RST, 0);
	DELAY(30);

	tries = 1000;
	do {
		u = bus_space_read_1(sc->st, sc->sh, ALS_ESP_RD_STATUS8);
		if (u & 0x80) {
			v = bus_space_read_1(sc->st, sc->sh, ALS_ESP_RD_DATA);
			if (v == 0xaa)
				return 0;
			else
				break;
		}
		DELAY(20);
	} while (--tries != 0);

	if (tries == 0)
		device_printf(sc->dev, "als_esp_reset timeout");
	return 1;
}