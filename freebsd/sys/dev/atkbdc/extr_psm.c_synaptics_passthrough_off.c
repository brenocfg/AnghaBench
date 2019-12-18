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
struct psm_softc {int /*<<< orphan*/  kbdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_scaling (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synaptics_preferred_mode (struct psm_softc*) ; 
 int /*<<< orphan*/  synaptics_set_mode (struct psm_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
synaptics_passthrough_off(struct psm_softc *sc)
{
	VLOG(2, (LOG_NOTICE, "psm: turning pass-through mode off.\n"));
	set_mouse_scaling(sc->kbdc, 2);
	set_mouse_scaling(sc->kbdc, 1);
	synaptics_set_mode(sc, synaptics_preferred_mode(sc));
}