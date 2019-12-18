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
struct g_raid_softc {int /*<<< orphan*/  sc_queue_mtx; } ;
struct g_raid_event {int e_flags; scalar_t__ e_error; int /*<<< orphan*/  e_event; int /*<<< orphan*/  e_tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,struct g_raid_event*) ; 
 int G_RAID_EVENT_DISK ; 
 int G_RAID_EVENT_DONE ; 
 int G_RAID_EVENT_SUBDISK ; 
 int G_RAID_EVENT_VOLUME ; 
 int G_RAID_EVENT_WAIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_raid_event_free (struct g_raid_event*) ; 
 scalar_t__ g_raid_update_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_raid_update_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_raid_update_subdisk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_raid_update_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_raid_event*) ; 

__attribute__((used)) static void
g_raid_handle_event(struct g_raid_softc *sc, struct g_raid_event *ep)
{

	if ((ep->e_flags & G_RAID_EVENT_VOLUME) != 0)
		ep->e_error = g_raid_update_volume(ep->e_tgt, ep->e_event);
	else if ((ep->e_flags & G_RAID_EVENT_DISK) != 0)
		ep->e_error = g_raid_update_disk(ep->e_tgt, ep->e_event);
	else if ((ep->e_flags & G_RAID_EVENT_SUBDISK) != 0)
		ep->e_error = g_raid_update_subdisk(ep->e_tgt, ep->e_event);
	else
		ep->e_error = g_raid_update_node(ep->e_tgt, ep->e_event);
	if ((ep->e_flags & G_RAID_EVENT_WAIT) == 0) {
		KASSERT(ep->e_error == 0,
		    ("Error cannot be handled."));
		g_raid_event_free(ep);
	} else {
		ep->e_flags |= G_RAID_EVENT_DONE;
		G_RAID_DEBUG1(4, sc, "Waking up %p.", ep);
		mtx_lock(&sc->sc_queue_mtx);
		wakeup(ep);
		mtx_unlock(&sc->sc_queue_mtx);
	}
}