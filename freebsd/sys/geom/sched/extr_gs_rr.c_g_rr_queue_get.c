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
struct g_rr_softc {int /*<<< orphan*/  sc_geom; } ;
struct g_rr_queue {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct g_rr_queue* g_sched_get_class (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static struct g_rr_queue *
g_rr_queue_get(struct g_rr_softc *sc, struct bio *bp)
{

	return (g_sched_get_class(sc->sc_geom, bp));
}