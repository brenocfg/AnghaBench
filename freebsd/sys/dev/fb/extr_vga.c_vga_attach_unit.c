#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* probe ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int (* init ) (int,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ video_switch_t ;
struct TYPE_6__ {int /*<<< orphan*/  adp; } ;
typedef  TYPE_2__ vga_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VGA_DRIVER_NAME ; 
 int stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub2 (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vid_get_switch (int /*<<< orphan*/ ) ; 

int
vga_attach_unit(int unit, vga_softc_t *sc, int flags)
{
	video_switch_t *sw;
	int error;

	sw = vid_get_switch(VGA_DRIVER_NAME);
	if (sw == NULL)
		return ENXIO;

	error = (*sw->probe)(unit, &sc->adp, NULL, flags);
	if (error)
		return error;
	return (*sw->init)(unit, sc->adp, flags);
}