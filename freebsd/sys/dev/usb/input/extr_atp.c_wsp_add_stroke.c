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
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ wsp_finger_t ;
struct atp_softc {int sc_n_strokes; int /*<<< orphan*/  sc_state; } ;
struct TYPE_6__ {int matched; int age; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  ctime; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ atp_stroke_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATP_DOUBLE_TAP_DRAG ; 
 int /*<<< orphan*/  ATP_LLEVEL_INFO ; 
 int /*<<< orphan*/  ATP_STROKE_TOUCH ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* atp_alloc_stroke (struct atp_softc*) ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wsp_add_stroke(struct atp_softc *sc, const wsp_finger_t *fingerp)
{
	atp_stroke_t *strokep;

	strokep = atp_alloc_stroke(sc);
	if (strokep == NULL)
		return;

	/*
	 * Strokes begin as potential touches. If a stroke survives
	 * longer than a threshold, or if it records significant
	 * cumulative movement, then it is considered a 'slide'.
	 */
	strokep->type    = ATP_STROKE_TOUCH;
	strokep->matched = true;
	microtime(&strokep->ctime);
	strokep->age = 1;	/* number of interrupts */
	strokep->x = fingerp->x;
	strokep->y = fingerp->y;

	/* Reset double-tap-n-drag if we have more than one strokes. */
	if (sc->sc_n_strokes > 1)
		sc->sc_state &= ~ATP_DOUBLE_TAP_DRAG;

	DPRINTFN(ATP_LLEVEL_INFO, "[%d,%d]\n", strokep->x, strokep->y);
}