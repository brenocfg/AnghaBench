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
typedef  int /*<<< orphan*/  u_char ;
struct g_mirror_softc {int sc_flags; int /*<<< orphan*/  sc_bump_id; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_lock; } ;
struct g_mirror_metadata {scalar_t__ md_mediasize; } ;
struct g_mirror_disk {int d_flags; struct g_consumer* d_consumer; struct g_mirror_softc* d_softc; } ;
struct g_consumer {int acr; int acw; int ace; TYPE_1__* provider; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ sectorsize; scalar_t__ mediasize; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_FP ; 
 int ENOSPC ; 
 int /*<<< orphan*/  G_MIRROR_BUMP_GENID ; 
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int G_MIRROR_DEVICE_FLAG_WIPE ; 
 int G_MIRROR_DISK_FLAG_BROKEN ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  G_MIRROR_EVENT_DONTWAIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KFAIL_POINT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_mirror_disconnect_on_failure ; 
 int /*<<< orphan*/  g_mirror_event_send (struct g_mirror_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_mirror_metadata_write ; 
 int g_mirror_ndisks (struct g_mirror_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int g_write_data (struct g_consumer*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mirror_metadata_encode (struct g_mirror_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_mirror_write_metadata(struct g_mirror_disk *disk,
    struct g_mirror_metadata *md)
{
	struct g_mirror_softc *sc;
	struct g_consumer *cp;
	off_t offset, length;
	u_char *sector;
	int error = 0;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);

	cp = disk->d_consumer;
	KASSERT(cp != NULL, ("NULL consumer (%s).", sc->sc_name));
	KASSERT(cp->provider != NULL, ("NULL provider (%s).", sc->sc_name));
	KASSERT(cp->acr >= 1 && cp->acw >= 1 && cp->ace >= 1,
	    ("Consumer %s closed? (r%dw%de%d).", cp->provider->name, cp->acr,
	    cp->acw, cp->ace));
	length = cp->provider->sectorsize;
	offset = cp->provider->mediasize - length;
	sector = malloc((size_t)length, M_MIRROR, M_WAITOK | M_ZERO);
	if (md != NULL &&
	    (sc->sc_flags & G_MIRROR_DEVICE_FLAG_WIPE) == 0) {
		/*
		 * Handle the case, when the size of parent provider reduced.
		 */
		if (offset < md->md_mediasize)
			error = ENOSPC;
		else
			mirror_metadata_encode(md, sector);
	}
	KFAIL_POINT_ERROR(DEBUG_FP, g_mirror_metadata_write, error);
	if (error == 0)
		error = g_write_data(cp, offset, sector, length);
	free(sector, M_MIRROR);
	if (error != 0) {
		if ((disk->d_flags & G_MIRROR_DISK_FLAG_BROKEN) == 0) {
			disk->d_flags |= G_MIRROR_DISK_FLAG_BROKEN;
			G_MIRROR_DEBUG(0, "Cannot write metadata on %s "
			    "(device=%s, error=%d).",
			    g_mirror_get_diskname(disk), sc->sc_name, error);
		} else {
			G_MIRROR_DEBUG(1, "Cannot write metadata on %s "
			    "(device=%s, error=%d).",
			    g_mirror_get_diskname(disk), sc->sc_name, error);
		}
		if (g_mirror_disconnect_on_failure &&
		    g_mirror_ndisks(sc, G_MIRROR_DISK_STATE_ACTIVE) > 1) {
			sc->sc_bump_id |= G_MIRROR_BUMP_GENID;
			g_mirror_event_send(disk,
			    G_MIRROR_DISK_STATE_DISCONNECTED,
			    G_MIRROR_EVENT_DONTWAIT);
		}
	}
	return (error);
}