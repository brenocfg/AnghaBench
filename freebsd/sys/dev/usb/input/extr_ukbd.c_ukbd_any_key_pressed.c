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
typedef  size_t uint8_t ;
struct TYPE_2__ {size_t* keycode; } ;
struct ukbd_softc {TYPE_1__ sc_odata; } ;

/* Variables and functions */
 size_t UKBD_NKEYCODE ; 

__attribute__((used)) static uint8_t
ukbd_any_key_pressed(struct ukbd_softc *sc)
{
	uint8_t i;
	uint8_t j;

	for (j = i = 0; i < UKBD_NKEYCODE; i++)
		j |= sc->sc_odata.keycode[i];

	return (j ? 1 : 0);
}