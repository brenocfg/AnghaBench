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
struct gv_volume {int dummy; } ;
struct gv_softc {int dummy; } ;
typedef  struct gv_volume gv_sd ;
typedef  struct gv_volume gv_plex ;
typedef  struct gv_volume gv_drive ;
struct gctl_req {int dummy; } ;
struct g_geom {struct gv_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_SET_DRIVE_STATE ; 
 int /*<<< orphan*/  GV_EVENT_SET_PLEX_STATE ; 
 int /*<<< orphan*/  GV_EVENT_SET_SD_STATE ; 
 int /*<<< orphan*/  GV_EVENT_SET_VOL_STATE ; 
 int GV_FLAG_F ; 
 int GV_SETSTATE_FORCE ; 
#define  GV_TYPE_DRIVE 131 
#define  GV_TYPE_PLEX 130 
#define  GV_TYPE_SD 129 
#define  GV_TYPE_VOL 128 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  gv_drivestatei (char*) ; 
 struct gv_volume* gv_find_drive (struct gv_softc*,char*) ; 
 struct gv_volume* gv_find_plex (struct gv_softc*,char*) ; 
 struct gv_volume* gv_find_sd (struct gv_softc*,char*) ; 
 struct gv_volume* gv_find_vol (struct gv_softc*,char*) ; 
 int gv_object_type (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  gv_plexstatei (char*) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_volume*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gv_sdstatei (char*) ; 
 int /*<<< orphan*/  gv_volstatei (char*) ; 

void
gv_setstate(struct g_geom *gp, struct gctl_req *req)
{
	struct gv_softc *sc;
	struct gv_sd *s;
	struct gv_drive *d;
	struct gv_volume *v;
	struct gv_plex *p;
	char *obj, *state;
	int f, *flags, type;

	f = 0;
	obj = gctl_get_param(req, "object", NULL);
	if (obj == NULL) {
		gctl_error(req, "no object given");
		return;
	}

	state = gctl_get_param(req, "state", NULL);
	if (state == NULL) {
		gctl_error(req, "no state given");
		return;
	}

	flags = gctl_get_paraml(req, "flags", sizeof(*flags));
	if (flags == NULL) {
		gctl_error(req, "no flags given");
		return;
	}

	if (*flags & GV_FLAG_F)
		f = GV_SETSTATE_FORCE;

	sc = gp->softc;
	type = gv_object_type(sc, obj);
	switch (type) {
	case GV_TYPE_VOL:
		if (gv_volstatei(state) < 0) {
			gctl_error(req, "invalid volume state '%s'", state);
			break;
		}
		v = gv_find_vol(sc, obj);
		gv_post_event(sc, GV_EVENT_SET_VOL_STATE, v, NULL,
		    gv_volstatei(state), f);
		break;

	case GV_TYPE_PLEX:
		if (gv_plexstatei(state) < 0) {
			gctl_error(req, "invalid plex state '%s'", state);
			break;
		}
		p = gv_find_plex(sc, obj);
		gv_post_event(sc, GV_EVENT_SET_PLEX_STATE, p, NULL,
		    gv_plexstatei(state), f);
		break;

	case GV_TYPE_SD:
		if (gv_sdstatei(state) < 0) {
			gctl_error(req, "invalid subdisk state '%s'", state);
			break;
		}
		s = gv_find_sd(sc, obj);
		gv_post_event(sc, GV_EVENT_SET_SD_STATE, s, NULL,
		    gv_sdstatei(state), f);
		break;

	case GV_TYPE_DRIVE:
		if (gv_drivestatei(state) < 0) {
			gctl_error(req, "invalid drive state '%s'", state);
			break;
		}
		d = gv_find_drive(sc, obj);
		gv_post_event(sc, GV_EVENT_SET_DRIVE_STATE, d, NULL,
		    gv_drivestatei(state), f);
		break;

	default:
		gctl_error(req, "unknown object '%s'", obj);
		break;
	}
}