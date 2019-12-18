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
struct gv_volume {int /*<<< orphan*/  wqueue; struct gv_softc* vinumconf; } ;
struct gv_softc {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_volume_start (struct gv_softc*,struct bio*) ; 

void
gv_volume_flush(struct gv_volume *v)
{
	struct gv_softc *sc;
	struct bio *bp;

	KASSERT(v != NULL, ("NULL v"));
	sc = v->vinumconf;
	KASSERT(sc != NULL, ("NULL sc"));

	bp = bioq_takefirst(v->wqueue);
	while (bp != NULL) {
		gv_volume_start(sc, bp);
		bp = bioq_takefirst(v->wqueue);
	}
}