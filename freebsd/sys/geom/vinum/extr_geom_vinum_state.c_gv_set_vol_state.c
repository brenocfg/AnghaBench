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
struct gv_volume {int state; int /*<<< orphan*/  vinumconf; int /*<<< orphan*/  provider; } ;

/* Variables and functions */
 int GV_ERR_ISBUSY ; 
 int GV_ERR_SETSTATE ; 
 int GV_SETSTATE_CONFIG ; 
 int GV_SETSTATE_FORCE ; 
#define  GV_VOL_DOWN 129 
#define  GV_VOL_UP 128 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gv_provider_is_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_save_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_update_vol_state (struct gv_volume*) ; 

int
gv_set_vol_state(struct gv_volume *v, int newstate, int flags)
{
	int oldstate;

	KASSERT(v != NULL, ("gv_set_vol_state: NULL v"));

	oldstate = v->state;

	if (newstate == oldstate)
		return (0);

	switch (newstate) {
	case GV_VOL_UP:
		/* Let update handle if the volume can come up. */
		gv_update_vol_state(v);
		if (v->state != GV_VOL_UP && !(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_SETSTATE);
		v->state = newstate;
		break;
	case GV_VOL_DOWN:
		/*
		 * Set state to GV_VOL_DOWN only if no-one is using the volume,
		 * or if the state should be forced.
		 */
		if (!gv_provider_is_open(v->provider) &&
		    !(flags & GV_SETSTATE_FORCE))
			return (GV_ERR_ISBUSY);
		v->state = newstate;
		break;
	}
	/* Save config */
	if (flags & GV_SETSTATE_CONFIG)
		gv_save_config(v->vinumconf);
	return (0);
}