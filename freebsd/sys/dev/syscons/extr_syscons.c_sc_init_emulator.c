#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int status; void* ts; TYPE_5__* rndr; TYPE_4__* tsw; TYPE_2__* sc; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_20__ {int (* te_init ) (TYPE_3__*,void**,int /*<<< orphan*/ ) ;scalar_t__ te_size; int /*<<< orphan*/  (* te_default_attr ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* te_term ) (TYPE_3__*,void**) ;int /*<<< orphan*/  te_renderer; } ;
typedef  TYPE_4__ sc_term_sw_t ;
struct TYPE_21__ {int /*<<< orphan*/  (* init ) (TYPE_3__*) ;} ;
typedef  TYPE_5__ sc_rndr_sw_t ;
struct TYPE_18__ {TYPE_1__* adp; } ;
struct TYPE_17__ {int /*<<< orphan*/  va_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int GRAPHICS_MODE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PIXEL_MODE ; 
 int /*<<< orphan*/  SC_NORM_ATTR ; 
 int /*<<< orphan*/  SC_NORM_REV_ATTR ; 
 int /*<<< orphan*/  SC_TE_COLD_INIT ; 
 int /*<<< orphan*/  SC_TE_WARM_INIT ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_clear_screen (TYPE_3__*) ; 
 scalar_t__ sc_malloc ; 
 TYPE_5__* sc_render_match (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* sc_term_match (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int stub3 (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,void**) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sc_init_emulator(scr_stat *scp, char *name)
{
    sc_term_sw_t *sw;
    sc_rndr_sw_t *rndr;
    void *p;
    int error;

    if (name == NULL)	/* if no name is given, use the current emulator */
	sw = scp->tsw;
    else		/* ...otherwise find the named emulator */
	sw = sc_term_match(name);
    if (sw == NULL)
	return EINVAL;

    rndr = NULL;
    if (strcmp(sw->te_renderer, "*") != 0) {
	rndr = sc_render_match(scp, sw->te_renderer,
			       scp->status & (GRAPHICS_MODE | PIXEL_MODE));
    }
    if (rndr == NULL) {
	rndr = sc_render_match(scp, scp->sc->adp->va_name,
			       scp->status & (GRAPHICS_MODE | PIXEL_MODE));
	if (rndr == NULL)
	    return ENODEV;
    }

    if (sw == scp->tsw) {
	error = (*sw->te_init)(scp, &scp->ts, SC_TE_WARM_INIT);
	scp->rndr = rndr;
	scp->rndr->init(scp);
	sc_clear_screen(scp);
	/* assert(error == 0); */
	return error;
    }

    if (sc_malloc && (sw->te_size > 0))
	p = malloc(sw->te_size, M_DEVBUF, M_NOWAIT);
    else
	p = NULL;
    error = (*sw->te_init)(scp, &p, SC_TE_COLD_INIT);
    if (error)
	return error;

    if (scp->tsw)
	(*scp->tsw->te_term)(scp, &scp->ts);
    if (scp->ts != NULL)
	free(scp->ts, M_DEVBUF);
    scp->tsw = sw;
    scp->ts = p;
    scp->rndr = rndr;
    scp->rndr->init(scp);

    (*sw->te_default_attr)(scp, SC_NORM_ATTR, SC_NORM_REV_ATTR);
    sc_clear_screen(scp);

    return 0;
}