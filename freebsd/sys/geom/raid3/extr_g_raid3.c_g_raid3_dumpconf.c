#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct sbuf {int dummy; } ;
struct TYPE_4__ {struct g_geom* ds_geom; } ;
struct g_raid3_softc {int sc_ndisks; int sc_mediasize; int sc_syncid; int sc_genid; scalar_t__ sc_flags; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_state; scalar_t__ sc_id; TYPE_3__* sc_zones; TYPE_1__ sc_sync; } ;
struct TYPE_5__ {int ds_offset; int ds_syncid; } ;
struct g_raid3_disk {int d_no; scalar_t__ d_state; int d_genid; scalar_t__ d_flags; TYPE_2__ d_sync; } ;
struct g_provider {int dummy; } ;
struct g_geom {struct g_raid3_softc* softc; } ;
struct g_consumer {struct g_raid3_disk* private; } ;
typedef  int intmax_t ;
struct TYPE_6__ {int sz_requested; int sz_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_FLAG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_FLAG_NOAUTOSYNC ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_FLAG_NOFAILSYNC ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_FLAG_ROUND_ROBIN ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_FLAG_VERIFY ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_BROKEN ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_DIRTY ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_FORCE_SYNC ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_HARDCODED ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_SYNCHRONIZING ; 
 scalar_t__ G_RAID3_DISK_STATE_SYNCHRONIZING ; 
 size_t G_RAID3_ZONE_16K ; 
 size_t G_RAID3_ZONE_4K ; 
 size_t G_RAID3_ZONE_64K ; 
 int g_raid3_device_state2str (int /*<<< orphan*/ ) ; 
 int g_raid3_disk_state2str (scalar_t__) ; 
 int /*<<< orphan*/  g_raid3_use_malloc ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_raid3_softc *sc;

	g_topology_assert();

	sc = gp->softc;
	if (sc == NULL)
		return;
	/* Skip synchronization geom. */
	if (gp == sc->sc_sync.ds_geom)
		return;
	if (pp != NULL) {
		/* Nothing here. */
	} else if (cp != NULL) {
		struct g_raid3_disk *disk;

		disk = cp->private;
		if (disk == NULL)
			return;
		g_topology_unlock();
		sx_xlock(&sc->sc_lock);
		sbuf_printf(sb, "%s<Type>", indent);
		if (disk->d_no == sc->sc_ndisks - 1)
			sbuf_cat(sb, "PARITY");
		else
			sbuf_cat(sb, "DATA");
		sbuf_cat(sb, "</Type>\n");
		sbuf_printf(sb, "%s<Number>%u</Number>\n", indent,
		    (u_int)disk->d_no);
		if (disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING) {
			sbuf_printf(sb, "%s<Synchronized>", indent);
			if (disk->d_sync.ds_offset == 0)
				sbuf_cat(sb, "0%");
			else {
				sbuf_printf(sb, "%u%%",
				    (u_int)((disk->d_sync.ds_offset * 100) /
				    (sc->sc_mediasize / (sc->sc_ndisks - 1))));
			}
			sbuf_cat(sb, "</Synchronized>\n");
			if (disk->d_sync.ds_offset > 0) {
				sbuf_printf(sb, "%s<BytesSynced>%jd"
				    "</BytesSynced>\n", indent,
				    (intmax_t)disk->d_sync.ds_offset);
			}
		}
		sbuf_printf(sb, "%s<SyncID>%u</SyncID>\n", indent,
		    disk->d_sync.ds_syncid);
		sbuf_printf(sb, "%s<GenID>%u</GenID>\n", indent, disk->d_genid);
		sbuf_printf(sb, "%s<Flags>", indent);
		if (disk->d_flags == 0)
			sbuf_cat(sb, "NONE");
		else {
			int first = 1;

#define	ADD_FLAG(flag, name)	do {					\
	if ((disk->d_flags & (flag)) != 0) {				\
		if (!first)						\
			sbuf_cat(sb, ", ");				\
		else							\
			first = 0;					\
		sbuf_cat(sb, name);					\
	}								\
} while (0)
			ADD_FLAG(G_RAID3_DISK_FLAG_DIRTY, "DIRTY");
			ADD_FLAG(G_RAID3_DISK_FLAG_HARDCODED, "HARDCODED");
			ADD_FLAG(G_RAID3_DISK_FLAG_SYNCHRONIZING,
			    "SYNCHRONIZING");
			ADD_FLAG(G_RAID3_DISK_FLAG_FORCE_SYNC, "FORCE_SYNC");
			ADD_FLAG(G_RAID3_DISK_FLAG_BROKEN, "BROKEN");
#undef	ADD_FLAG
		}
		sbuf_cat(sb, "</Flags>\n");
		sbuf_printf(sb, "%s<State>%s</State>\n", indent,
		    g_raid3_disk_state2str(disk->d_state));
		sx_xunlock(&sc->sc_lock);
		g_topology_lock();
	} else {
		g_topology_unlock();
		sx_xlock(&sc->sc_lock);
		if (!g_raid3_use_malloc) {
			sbuf_printf(sb,
			    "%s<Zone4kRequested>%u</Zone4kRequested>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_4K].sz_requested);
			sbuf_printf(sb,
			    "%s<Zone4kFailed>%u</Zone4kFailed>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_4K].sz_failed);
			sbuf_printf(sb,
			    "%s<Zone16kRequested>%u</Zone16kRequested>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_16K].sz_requested);
			sbuf_printf(sb,
			    "%s<Zone16kFailed>%u</Zone16kFailed>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_16K].sz_failed);
			sbuf_printf(sb,
			    "%s<Zone64kRequested>%u</Zone64kRequested>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_64K].sz_requested);
			sbuf_printf(sb,
			    "%s<Zone64kFailed>%u</Zone64kFailed>\n", indent,
			    sc->sc_zones[G_RAID3_ZONE_64K].sz_failed);
		}
		sbuf_printf(sb, "%s<ID>%u</ID>\n", indent, (u_int)sc->sc_id);
		sbuf_printf(sb, "%s<SyncID>%u</SyncID>\n", indent, sc->sc_syncid);
		sbuf_printf(sb, "%s<GenID>%u</GenID>\n", indent, sc->sc_genid);
		sbuf_printf(sb, "%s<Flags>", indent);
		if (sc->sc_flags == 0)
			sbuf_cat(sb, "NONE");
		else {
			int first = 1;

#define	ADD_FLAG(flag, name)	do {					\
	if ((sc->sc_flags & (flag)) != 0) {				\
		if (!first)						\
			sbuf_cat(sb, ", ");				\
		else							\
			first = 0;					\
		sbuf_cat(sb, name);					\
	}								\
} while (0)
			ADD_FLAG(G_RAID3_DEVICE_FLAG_NOFAILSYNC, "NOFAILSYNC");
			ADD_FLAG(G_RAID3_DEVICE_FLAG_NOAUTOSYNC, "NOAUTOSYNC");
			ADD_FLAG(G_RAID3_DEVICE_FLAG_ROUND_ROBIN,
			    "ROUND-ROBIN");
			ADD_FLAG(G_RAID3_DEVICE_FLAG_VERIFY, "VERIFY");
#undef	ADD_FLAG
		}
		sbuf_cat(sb, "</Flags>\n");
		sbuf_printf(sb, "%s<Components>%u</Components>\n", indent,
		    sc->sc_ndisks);
		sbuf_printf(sb, "%s<State>%s</State>\n", indent,
		    g_raid3_device_state2str(sc->sc_state));
		sx_xunlock(&sc->sc_lock);
		g_topology_lock();
	}
}