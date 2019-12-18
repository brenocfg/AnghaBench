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
struct gv_volume {int plexcount; } ;
struct gv_plex {int state; int /*<<< orphan*/  vinumconf; struct gv_volume* vol_sc; } ;

/* Variables and functions */
 int GV_ERR_SETSTATE ; 
#define  GV_PLEX_DEGRADED 130 
#define  GV_PLEX_DOWN 129 
#define  GV_PLEX_UP 128 
 int GV_SETSTATE_CONFIG ; 
 int GV_SETSTATE_FORCE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int gv_plexdown (struct gv_volume*) ; 
 int /*<<< orphan*/  gv_save_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_update_plex_state (struct gv_plex*) ; 
 int /*<<< orphan*/  gv_update_vol_state (struct gv_volume*) ; 

int
gv_set_plex_state(struct gv_plex *p, int newstate, int flags)
{
	struct gv_volume *v;
	int oldstate, plexdown;

	KASSERT(p != NULL, ("gv_set_plex_state: NULL p"));

	oldstate = p->state;
	v = p->vol_sc;
	plexdown = 0;

	if (newstate == oldstate)
		return (0);

	switch (newstate) {
	case GV_PLEX_UP:
		/* Let update_plex handle if the plex can come up */
		gv_update_plex_state(p);
		if (p->state != GV_PLEX_UP && !(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_SETSTATE);
		p->state = newstate;
		break;
	case GV_PLEX_DOWN:
		/*
		 * Set state to GV_PLEX_DOWN only if no-one is using the plex,
		 * or if the state is forced.
		 */
		if (v != NULL) {
			/* If the only one up, force is needed. */
			plexdown = gv_plexdown(v);
			if ((v->plexcount == 1 ||
			    (v->plexcount - plexdown == 1)) &&
			    ((flags & GV_SETSTATE_FORCE) == 0))
				return (GV_ERR_SETSTATE);
		}
		p->state = newstate;
		break;
	case GV_PLEX_DEGRADED:
		/* Only used internally, so we have to be forced. */
		if (flags & GV_SETSTATE_FORCE)
			p->state = newstate;
		break;
	}

	/* Update our volume if we have one. */
	if (v != NULL)
		gv_update_vol_state(v);

	/* Save config. */
	if (flags & GV_SETSTATE_CONFIG)
		gv_save_config(p->vinumconf);
	return (0);
}