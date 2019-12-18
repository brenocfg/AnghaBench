#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct atp_softc {int sc_n_strokes; int /*<<< orphan*/  sc_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  cum; int /*<<< orphan*/  loc; } ;
typedef  TYPE_2__ fg_pspan ;
struct TYPE_11__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {int matched; int age; TYPE_4__ ctime; TYPE_1__* components; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ atp_stroke_t ;
struct TYPE_8__ {int matched; int /*<<< orphan*/  loc; int /*<<< orphan*/  max_cum_pressure; int /*<<< orphan*/  cum_pressure; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATP_DOUBLE_TAP_DRAG ; 
 int /*<<< orphan*/  ATP_LLEVEL_INFO ; 
 int /*<<< orphan*/  ATP_STROKE_TOUCH ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 size_t X ; 
 size_t Y ; 
 TYPE_3__* atp_alloc_stroke (struct atp_softc*) ; 
 int /*<<< orphan*/  microtime (TYPE_4__*) ; 

__attribute__((used)) static void
fg_add_stroke(struct atp_softc *sc, const fg_pspan *pspan_x,
    const fg_pspan *pspan_y)
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
	strokep->matched = false;
	microtime(&strokep->ctime);
	strokep->age     = 1;		/* number of interrupts */
	strokep->x       = pspan_x->loc;
	strokep->y       = pspan_y->loc;

	strokep->components[X].loc              = pspan_x->loc;
	strokep->components[X].cum_pressure     = pspan_x->cum;
	strokep->components[X].max_cum_pressure = pspan_x->cum;
	strokep->components[X].matched          = true;

	strokep->components[Y].loc              = pspan_y->loc;
	strokep->components[Y].cum_pressure     = pspan_y->cum;
	strokep->components[Y].max_cum_pressure = pspan_y->cum;
	strokep->components[Y].matched          = true;

	if (sc->sc_n_strokes > 1) {
		/* Reset double-tap-n-drag if we have more than one strokes. */
		sc->sc_state &= ~ATP_DOUBLE_TAP_DRAG;
	}

	DPRINTFN(ATP_LLEVEL_INFO, "[%u,%u], time: %u,%ld\n",
	    strokep->components[X].loc,
	    strokep->components[Y].loc,
	    (u_int)strokep->ctime.tv_sec,
	    (unsigned long int)strokep->ctime.tv_usec);
}