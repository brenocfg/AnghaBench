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
 int bus_read_1 (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* esp__read_regnames ; 
 scalar_t__ esp_sbus_debug ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 

__attribute__((used)) static uint8_t
esp_read_reg(struct ncr53c9x_softc *sc, int reg)
{
	struct esp_softc *esc = (struct esp_softc *)sc;
	uint8_t v;

	v = bus_read_1(esc->sc_res, reg * 4);

#ifdef ESP_SBUS_DEBUG
	if (esp_sbus_debug && (reg < 0x10) && esp__read_regnames[reg].r_flag)
		printf("RD:%x <%s> %x\n", reg * 4, ((unsigned)reg < 0x10) ?
		    esp__read_regnames[reg].r_name : "<***>", v);
#endif

	return (v);
}