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
struct sfxge_intr {int type; int n_alloc; struct sfxge_intr_hdl* table; } ;
struct sfxge_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * evq; struct sfxge_intr intr; } ;
struct sfxge_intr_hdl {int /*<<< orphan*/  eih_tag; int /*<<< orphan*/  eih_res; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
#define  EFX_INTR_LINE 129 
#define  EFX_INTR_MESSAGE 128 
 int EINVAL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bus_bind_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rss_getcpu (int) ; 
 int /*<<< orphan*/ * sfxge_intr_line ; 
 int /*<<< orphan*/ * sfxge_intr_line_filter ; 
 int /*<<< orphan*/ * sfxge_intr_message ; 

__attribute__((used)) static int
sfxge_intr_bus_enable(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	struct sfxge_intr_hdl *table;
	driver_filter_t *filter;
	driver_intr_t *handler;
	int index;
	int err;

	intr = &sc->intr;
	table = intr->table;

	switch (intr->type) {
	case EFX_INTR_MESSAGE:
		filter = NULL; /* not shared */
		handler = sfxge_intr_message;
		break;

	case EFX_INTR_LINE:
		filter = sfxge_intr_line_filter;
		handler = sfxge_intr_line;
		break;

	default:
		KASSERT(0, ("Invalid interrupt type"));
		return (EINVAL);
	}

	/* Try to add the handlers */
	for (index = 0; index < intr->n_alloc; index++) {
		if ((err = bus_setup_intr(sc->dev, table[index].eih_res,
			    INTR_MPSAFE|INTR_TYPE_NET, filter, handler,
			    sc->evq[index], &table[index].eih_tag)) != 0) {
			goto fail;
		}
#ifdef SFXGE_HAVE_DESCRIBE_INTR
		if (intr->n_alloc > 1)
			bus_describe_intr(sc->dev, table[index].eih_res,
			    table[index].eih_tag, "%d", index);
#endif
#ifdef RSS
		bus_bind_intr(sc->dev, table[index].eih_res,
			      rss_getcpu(index));
#else
		bus_bind_intr(sc->dev, table[index].eih_res, index);
#endif

	}

	return (0);

fail:
	/* Remove remaining handlers */
	while (--index >= 0)
		bus_teardown_intr(sc->dev, table[index].eih_res,
		    table[index].eih_tag);

	return (err);
}