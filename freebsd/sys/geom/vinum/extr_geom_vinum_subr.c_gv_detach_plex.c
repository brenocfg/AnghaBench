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
struct gv_volume {int /*<<< orphan*/ * last_read_plex; int /*<<< orphan*/  plexcount; int /*<<< orphan*/  provider; } ;
struct gv_plex {scalar_t__ state; int /*<<< orphan*/  vinumconf; int /*<<< orphan*/  volume; struct gv_volume* vol_sc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GV_ERR_ISBUSY ; 
 int GV_FLAG_F ; 
 int /*<<< orphan*/  GV_MAXVOLNAME ; 
 scalar_t__ GV_PLEX_UP ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gv_plex*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 scalar_t__ gv_provider_is_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_save_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_update_vol_size (struct gv_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_vol_size (struct gv_volume*) ; 
 int /*<<< orphan*/  in_volume ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gv_detach_plex(struct gv_plex *p, int flags)
{
	struct gv_volume *v;

	g_topology_assert();
	v = p->vol_sc;

	if (v == NULL) {
		G_VINUM_DEBUG(1, "unable to detach %s: already detached",
		    p->name);
		return (0); /* Not an error. */
	}

	/*
	 * Only proceed if forced or volume inactive.
	 */
	if (!(flags & GV_FLAG_F) && (gv_provider_is_open(v->provider) ||
	    p->state == GV_PLEX_UP)) {
		G_VINUM_DEBUG(1, "unable to detach %s: volume %s is busy",
		    p->name, p->volume);
		return (GV_ERR_ISBUSY);
	}
	v->plexcount--;
	/* Make sure someone don't read us when gone. */
	v->last_read_plex = NULL; 
	LIST_REMOVE(p, in_volume);
	p->vol_sc = NULL;
	memset(p->volume, 0, GV_MAXVOLNAME);
	gv_update_vol_size(v, gv_vol_size(v));
	gv_save_config(p->vinumconf);
	return (0);
}