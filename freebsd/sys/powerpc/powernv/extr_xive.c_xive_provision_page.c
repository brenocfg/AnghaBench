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
struct xive_softc {int /*<<< orphan*/  sc_prov_page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  M_XIVE ; 
 int /*<<< orphan*/  OPAL_XIVE_DONATE_PAGE ; 
 int OPAL_XIVE_PROVISIONING ; 
 void* contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opal_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (void*) ; 

__attribute__((used)) static int
xive_provision_page(struct xive_softc *sc)
{
	void *prov_page;
	int error;

	do {
		prov_page = contigmalloc(sc->sc_prov_page_size, M_XIVE, 0,
		    0, BUS_SPACE_MAXADDR,
		    sc->sc_prov_page_size, sc->sc_prov_page_size);

		error = opal_call(OPAL_XIVE_DONATE_PAGE, -1,
		    vtophys(prov_page));
	} while (error == OPAL_XIVE_PROVISIONING);

	return (0);
}