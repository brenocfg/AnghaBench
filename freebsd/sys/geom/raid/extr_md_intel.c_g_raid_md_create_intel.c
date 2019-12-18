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
struct g_raid_md_intel_object {int mdio_config_id; int mdio_orig_config_id; scalar_t__ mdio_generation; } ;
struct g_geom {int dummy; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int G_RAID_MD_TASTE_FAIL ; 
 int G_RAID_MD_TASTE_NEW ; 
 int arc4random () ; 
 struct g_raid_softc* g_raid_create_node (struct g_class*,char*,struct g_raid_md_object*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
g_raid_md_create_intel(struct g_raid_md_object *md, struct g_class *mp,
    struct g_geom **gp)
{
	struct g_raid_softc *sc;
	struct g_raid_md_intel_object *mdi;
	char name[16];

	mdi = (struct g_raid_md_intel_object *)md;
	mdi->mdio_config_id = mdi->mdio_orig_config_id = arc4random();
	mdi->mdio_generation = 0;
	snprintf(name, sizeof(name), "Intel-%08x", mdi->mdio_config_id);
	sc = g_raid_create_node(mp, name, md);
	if (sc == NULL)
		return (G_RAID_MD_TASTE_FAIL);
	md->mdo_softc = sc;
	*gp = sc->sc_geom;
	return (G_RAID_MD_TASTE_NEW);
}