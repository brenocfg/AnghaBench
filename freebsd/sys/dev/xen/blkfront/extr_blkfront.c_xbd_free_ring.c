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
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct xbd_softc {int xbd_ring_pages; scalar_t__* xbd_ring_ref; TYPE_1__ xbd_ring; } ;

/* Variables and functions */
 scalar_t__ GRANT_REF_INVALID ; 
 int /*<<< orphan*/  M_XENBLOCKFRONT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_ref (scalar_t__) ; 

__attribute__((used)) static void
xbd_free_ring(struct xbd_softc *sc)
{
	int i;

	if (sc->xbd_ring.sring == NULL)
		return;

	for (i = 0; i < sc->xbd_ring_pages; i++) {
		if (sc->xbd_ring_ref[i] != GRANT_REF_INVALID) {
			gnttab_end_foreign_access_ref(sc->xbd_ring_ref[i]);
			sc->xbd_ring_ref[i] = GRANT_REF_INVALID;
		}
	}
	free(sc->xbd_ring.sring, M_XENBLOCKFRONT);
	sc->xbd_ring.sring = NULL;
}