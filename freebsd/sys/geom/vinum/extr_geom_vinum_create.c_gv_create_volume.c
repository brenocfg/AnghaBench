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
struct gv_volume {int /*<<< orphan*/  wqueue; int /*<<< orphan*/  plexes; int /*<<< orphan*/  flags; struct gv_softc* vinumconf; } ;
struct gv_softc {int /*<<< orphan*/  volumes; } ;
struct bio_queue_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_VOL_NEWBORN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gv_volume*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_malloc (int,int) ; 
 int /*<<< orphan*/  volume ; 

int
gv_create_volume(struct gv_softc *sc, struct gv_volume *v)
{
	KASSERT(v != NULL, ("gv_create_volume: NULL v"));

	v->vinumconf = sc;
	v->flags |= GV_VOL_NEWBORN;
	LIST_INIT(&v->plexes);
	LIST_INSERT_HEAD(&sc->volumes, v, volume);
	v->wqueue = g_malloc(sizeof(struct bio_queue_head), M_WAITOK | M_ZERO);
	bioq_init(v->wqueue);
	return (0);
}