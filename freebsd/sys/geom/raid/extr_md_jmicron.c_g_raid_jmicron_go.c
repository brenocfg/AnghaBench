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
struct g_raid_softc {struct g_raid_md_object* sc_md; } ;
struct g_raid_md_object {int dummy; } ;
struct g_raid_md_jmicron_object {int /*<<< orphan*/  mdio_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int /*<<< orphan*/ ,struct g_raid_softc*,char*) ; 
 int /*<<< orphan*/  G_RAID_NODE_E_START ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_jmicron_go(void *arg)
{
	struct g_raid_softc *sc;
	struct g_raid_md_object *md;
	struct g_raid_md_jmicron_object *mdi;

	sc = arg;
	md = sc->sc_md;
	mdi = (struct g_raid_md_jmicron_object *)md;
	if (!mdi->mdio_started) {
		G_RAID_DEBUG1(0, sc, "Force array start due to timeout.");
		g_raid_event_send(sc, G_RAID_NODE_E_START, 0);
	}
}