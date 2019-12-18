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
typedef  struct gv_volume gv_plex ;
struct gctl_req {int dummy; } ;
struct g_geom {struct gv_softc* softc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_START_PLEX ; 
 int /*<<< orphan*/  GV_EVENT_START_VOLUME ; 
#define  GV_TYPE_DRIVE 131 
#define  GV_TYPE_PLEX 130 
#define  GV_TYPE_SD 129 
#define  GV_TYPE_VOL 128 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct gv_volume* gv_find_plex (struct gv_softc*,char*) ; 
 struct gv_volume* gv_find_vol (struct gv_softc*,char*) ; 
 int gv_object_type (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_volume*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
gv_start_obj(struct g_geom *gp, struct gctl_req *req)
{
	struct gv_softc *sc;
	struct gv_volume *v;
	struct gv_plex *p;
	int *argc, *initsize;
	char *argv, buf[20];
	int i, type;

	argc = gctl_get_paraml(req, "argc", sizeof(*argc));
	initsize = gctl_get_paraml(req, "initsize", sizeof(*initsize));

	if (argc == NULL || *argc == 0) {
		gctl_error(req, "no arguments given");
		return;
	}

	sc = gp->softc;

	for (i = 0; i < *argc; i++) {
		snprintf(buf, sizeof(buf), "argv%d", i);
		argv = gctl_get_param(req, buf, NULL);
		if (argv == NULL)
			continue;
		type = gv_object_type(sc, argv);
		switch (type) {
		case GV_TYPE_VOL:
			v = gv_find_vol(sc, argv);
			if (v != NULL)
				gv_post_event(sc, GV_EVENT_START_VOLUME, v,
				    NULL, *initsize, 0);
			break;

		case GV_TYPE_PLEX:
			p = gv_find_plex(sc, argv);
			if (p != NULL)
				gv_post_event(sc, GV_EVENT_START_PLEX, p, NULL,
				    *initsize, 0);
			break;

		case GV_TYPE_SD:
		case GV_TYPE_DRIVE:
			/* XXX Not implemented, but what is the use? */
			gctl_error(req, "unable to start '%s' - not yet supported",
			    argv);
			return;
		default:
			gctl_error(req, "unknown object '%s'", argv);
			return;
		}
	}
}