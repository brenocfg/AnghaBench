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
struct gv_sd {int state; int flags; int /*<<< orphan*/  vinumconf; struct gv_plex* plex_sc; struct gv_drive* drive_sc; } ;
struct gv_plex {int flags; int /*<<< orphan*/  org; int /*<<< orphan*/  synced; TYPE_1__* vol_sc; } ;
struct gv_drive {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int plexcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_DRIVE_UP ; 
 int GV_ERR_INVSTATE ; 
 int GV_ERR_ISATTACHED ; 
 int GV_ERR_SETSTATE ; 
 int /*<<< orphan*/  GV_PLEX_RAID5 ; 
 int GV_PLEX_SYNCING ; 
 int GV_SD_CANGOUP ; 
#define  GV_SD_DOWN 132 
#define  GV_SD_INITIALIZING 131 
#define  GV_SD_REVIVING 130 
#define  GV_SD_STALE 129 
#define  GV_SD_UP 128 
 int GV_SETSTATE_CONFIG ; 
 int GV_SETSTATE_FORCE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gv_save_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_update_plex_state (struct gv_plex*) ; 

int
gv_set_sd_state(struct gv_sd *s, int newstate, int flags)
{
	struct gv_drive *d;
	struct gv_plex *p;
	int oldstate, status;

	KASSERT(s != NULL, ("gv_set_sd_state: NULL s"));

	oldstate = s->state;

	/* We are optimistic and assume it will work. */
	status = 0;
	
	if (newstate == oldstate)
		return (0);

	switch (newstate) {
	case GV_SD_DOWN:
		/*
		 * If we're attached to a plex, we won't go down without use of
		 * force.
		 */
		if ((s->plex_sc != NULL) && !(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_ISATTACHED);
		break;

	case GV_SD_REVIVING:
	case GV_SD_INITIALIZING:
		/*
		 * Only do this if we're forced, since it usually is done
		 * internally, and then we do use the force flag. 
		 */
		if (!(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_SETSTATE);
		break;

	case GV_SD_UP:
		/* We can't bring the subdisk up if our drive is dead. */
		d = s->drive_sc;
		if ((d == NULL) || (d->state != GV_DRIVE_UP))
			return (GV_ERR_SETSTATE);

		/* Check from where we want to be brought up. */
		switch (s->state) {
		case GV_SD_REVIVING:
		case GV_SD_INITIALIZING:
			/*
			 * The subdisk was initializing.  We allow it to be
			 * brought up.
			 */
			break;

		case GV_SD_DOWN:
			/*
			 * The subdisk is currently down.  We allow it to be
			 * brought up if it is not attached to a plex.
			 */
			p = s->plex_sc;
			if (p == NULL)
				break;

			/*
			 * If this subdisk is attached to a plex, we allow it
			 * to be brought up if the plex if it's not a RAID5
			 * plex, otherwise it's made 'stale'.
			 */

			if (p->org != GV_PLEX_RAID5)
				break;
			else if (s->flags & GV_SD_CANGOUP) {
				s->flags &= ~GV_SD_CANGOUP;
				break;
			} else if (flags & GV_SETSTATE_FORCE)
				break;
			else
				s->state = GV_SD_STALE;

			status = GV_ERR_SETSTATE;
			break;

		case GV_SD_STALE:
			/*
			 * A stale subdisk can be brought up only if it's part
			 * of a concat or striped plex that's the only one in a
			 * volume, or if the subdisk isn't attached to a plex.
			 * Otherwise it needs to be revived or initialized
			 * first.
			 */
			p = s->plex_sc;
			if (p == NULL || flags & GV_SETSTATE_FORCE)
				break;

			if ((p->org != GV_PLEX_RAID5 &&
			    p->vol_sc->plexcount == 1) ||
			    (p->flags & GV_PLEX_SYNCING &&
			    p->synced > 0 &&
			    p->org == GV_PLEX_RAID5))
				break;
			else
				return (GV_ERR_SETSTATE);

		default:
			return (GV_ERR_INVSTATE);
		}
		break;

	/* Other state transitions are only possible with force. */
	default:
		if (!(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_SETSTATE);
	}

	/* We can change the state and do it. */
	if (status == 0)
		s->state = newstate;

	/* Update our plex, if we're attached to one. */
	if (s->plex_sc != NULL)
		gv_update_plex_state(s->plex_sc);

	/* Save the config back to disk. */
	if (flags & GV_SETSTATE_CONFIG)
		gv_save_config(s->vinumconf);

	return (status);
}