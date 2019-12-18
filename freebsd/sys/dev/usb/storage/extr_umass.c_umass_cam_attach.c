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
struct umass_softc {char* sc_name; int sc_unit; int /*<<< orphan*/  sc_sim; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 

__attribute__((used)) static void
umass_cam_attach(struct umass_softc *sc)
{
#ifndef USB_DEBUG
	if (bootverbose)
#endif
		printf("%s:%d:%d: Attached to scbus%d\n",
		    sc->sc_name, cam_sim_path(sc->sc_sim),
		    sc->sc_unit, cam_sim_path(sc->sc_sim));
}