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
typedef  int u_int ;
struct ofwfb_softc {int /*<<< orphan*/ * sc_tag; } ;
struct TYPE_2__ {int red; int green; int blue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bs_le_tag ; 
 TYPE_1__* ofwfb_cmap ; 

__attribute__((used)) static u_int
ofwfb_pix32(struct ofwfb_softc *sc, int attr)
{
	u_int retval;

	if (sc->sc_tag == &bs_le_tag)
		retval = (ofwfb_cmap[attr].red << 16) |
			(ofwfb_cmap[attr].green << 8) |
			ofwfb_cmap[attr].blue;
	else
		retval = (ofwfb_cmap[attr].blue  << 16) |
			(ofwfb_cmap[attr].green << 8) |
			ofwfb_cmap[attr].red;

	return (retval);
}