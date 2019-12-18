#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ncr53c9x_softc {int dummy; } ;
struct esp_softc {int /*<<< orphan*/  sc_res; } ;
struct TYPE_2__ {char* r_name; scalar_t__ r_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* esp__write_regnames ; 
 scalar_t__ esp_sbus_debug ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 

__attribute__((used)) static void
esp_write_reg(struct ncr53c9x_softc *sc, int reg, uint8_t v)
{
	struct esp_softc *esc = (struct esp_softc *)sc;

#ifdef ESP_SBUS_DEBUG
	if (esp_sbus_debug && (reg < 0x10) && esp__write_regnames[reg].r_flag)
		printf("WR:%x <%s> %x\n", reg * 4, ((unsigned)reg < 0x10) ?
		    esp__write_regnames[reg].r_name : "<***>", v);
#endif

	bus_write_1(esc->sc_res, reg * 4, v);
}