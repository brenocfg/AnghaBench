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
struct gv_sd {scalar_t__ state; int /*<<< orphan*/  vinumconf; int /*<<< orphan*/  plex; struct gv_plex* plex_sc; int /*<<< orphan*/  name; } ;
struct gv_plex {scalar_t__ state; int /*<<< orphan*/  sddetached; } ;

/* Variables and functions */
 int GV_ERR_ISBUSY ; 
 int GV_FLAG_F ; 
 int /*<<< orphan*/  GV_MAXPLEXNAME ; 
 scalar_t__ GV_PLEX_DEGRADED ; 
 scalar_t__ GV_SD_UP ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gv_sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gv_save_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_plex ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gv_detach_sd(struct gv_sd *s, int flags)
{
	struct gv_plex *p;

	g_topology_assert();
	p = s->plex_sc;

	if (p == NULL) {
		G_VINUM_DEBUG(1, "unable to detach %s: already detached",
		    s->name);
		return (0); /* Not an error. */
	}

	/*
	 * Don't proceed if we're not forcing, and the plex is up, or degraded
	 * with this subdisk up.
	 */
	if (!(flags & GV_FLAG_F) && ((p->state > GV_PLEX_DEGRADED) ||
	    ((p->state == GV_PLEX_DEGRADED) && (s->state == GV_SD_UP)))) {
	    	G_VINUM_DEBUG(1, "unable to detach %s: plex %s is busy",
		    s->name, s->plex);
		return (GV_ERR_ISBUSY);
	}

	LIST_REMOVE(s, in_plex);
	s->plex_sc = NULL;
	memset(s->plex, 0, GV_MAXPLEXNAME);
	p->sddetached++;
	gv_save_config(s->vinumconf);
	return (0);
}