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
typedef  int uint32_t ;
struct udl_softc {unsigned int sc_cur_mode; } ;
struct TYPE_2__ {scalar_t__ vdisplay; scalar_t__ hdisplay; } ;

/* Variables and functions */
 TYPE_1__* udl_modes ; 

__attribute__((used)) static uint32_t
udl_get_fb_size(struct udl_softc *sc)
{
	unsigned i = sc->sc_cur_mode;

	return ((uint32_t)udl_modes[i].hdisplay *
	    (uint32_t)udl_modes[i].vdisplay * 2);
}