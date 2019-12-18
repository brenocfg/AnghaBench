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
struct targbh_softc {int init_level; int /*<<< orphan*/  state; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SCSIBH ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  TARGBH_STATE_TEARDOWN ; 
 int /*<<< orphan*/  cam_periph_sleep (struct cam_periph*,struct targbh_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct targbh_softc*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  targbhdislun (struct cam_periph*) ; 

__attribute__((used)) static void
targbhdtor(struct cam_periph *periph)
{
	struct targbh_softc *softc;

	softc = (struct targbh_softc *)periph->softc;

	softc->state = TARGBH_STATE_TEARDOWN;

	targbhdislun(periph);

	switch (softc->init_level) {
	case 0:
		panic("targdtor - impossible init level");
	case 1:
		/* FALLTHROUGH */
	default:
		/* XXX Wait for callback of targbhdislun() */
		cam_periph_sleep(periph, softc, PRIBIO, "targbh", hz/2);
		free(softc, M_SCSIBH);
		break;
	}
}