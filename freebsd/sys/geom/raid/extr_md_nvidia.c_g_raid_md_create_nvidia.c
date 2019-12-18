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
struct g_raid_softc {struct g_geom* sc_geom; } ;
struct g_raid_md_object {struct g_raid_softc* mdo_softc; } ;
struct g_raid_md_nvidia_object {int /*<<< orphan*/  mdio_volume_id; } ;
struct g_geom {int dummy; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int G_RAID_MD_TASTE_FAIL ; 
 int G_RAID_MD_TASTE_NEW ; 
 int /*<<< orphan*/  NVIDIANodeID ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 struct g_raid_softc* g_raid_create_node (struct g_class*,char*,struct g_raid_md_object*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
g_raid_md_create_nvidia(struct g_raid_md_object *md, struct g_class *mp,
    struct g_geom **gp)
{
	struct g_raid_softc *sc;
	struct g_raid_md_nvidia_object *mdi;
	char name[32];

	mdi = (struct g_raid_md_nvidia_object *)md;
	arc4rand(&mdi->mdio_volume_id, 16, 0);
	snprintf(name, sizeof(name), "NVIDIA-%d",
	    atomic_fetchadd_int(&NVIDIANodeID, 1));
	sc = g_raid_create_node(mp, name, md);
	if (sc == NULL)
		return (G_RAID_MD_TASTE_FAIL);
	md->mdo_softc = sc;
	*gp = sc->sc_geom;
	return (G_RAID_MD_TASTE_NEW);
}