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
struct g_raid_md_sii_object {int* mdio_timestamp; scalar_t__ mdio_generation; void* mdio_location; } ;
struct g_raid_md_object {struct g_raid_softc* mdo_softc; } ;
struct g_geom {int dummy; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int G_RAID_MD_TASTE_FAIL ; 
 int G_RAID_MD_TASTE_NEW ; 
 void* arc4random () ; 
 struct g_raid_softc* g_raid_create_node (struct g_class*,char*,struct g_raid_md_object*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
g_raid_md_create_sii(struct g_raid_md_object *md, struct g_class *mp,
    struct g_geom **gp)
{
	struct g_raid_softc *sc;
	struct g_raid_md_sii_object *mdi;
	char name[32];

	mdi = (struct g_raid_md_sii_object *)md;
	mdi->mdio_timestamp[5] = arc4random();
	mdi->mdio_timestamp[4] = arc4random();
	mdi->mdio_timestamp[3] = arc4random();
	mdi->mdio_timestamp[2] = arc4random();
	mdi->mdio_timestamp[1] = arc4random();
	mdi->mdio_timestamp[0] = arc4random();
	mdi->mdio_location = arc4random();
	mdi->mdio_generation = 0;
	snprintf(name, sizeof(name), "SiI-%02x%02x%02x%02x%02x%02x",
	    mdi->mdio_timestamp[5], mdi->mdio_timestamp[4],
	    mdi->mdio_timestamp[3], mdi->mdio_timestamp[2],
	    mdi->mdio_timestamp[1], mdi->mdio_timestamp[0]);
	sc = g_raid_create_node(mp, name, md);
	if (sc == NULL)
		return (G_RAID_MD_TASTE_FAIL);
	md->mdo_softc = sc;
	*gp = sc->sc_geom;
	return (G_RAID_MD_TASTE_NEW);
}