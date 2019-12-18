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
struct gv_softc {int dummy; } ;
struct gv_plex {int /*<<< orphan*/  rqueue; struct gv_softc* vinumconf; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bioq_takefirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_plex_start (struct gv_plex*,struct bio*) ; 

__attribute__((used)) static void
gv_plex_flush(struct gv_plex *p)
{
	struct gv_softc *sc;
	struct bio *bp;

	sc = p->vinumconf;
	bp = bioq_takefirst(p->rqueue);
	while (bp != NULL) {
		gv_plex_start(p, bp);
		bp = bioq_takefirst(p->rqueue);
	}
}