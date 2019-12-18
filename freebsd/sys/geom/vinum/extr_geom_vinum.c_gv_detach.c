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
struct gv_softc {int dummy; } ;
struct gv_sd {int dummy; } ;
typedef  struct gv_sd gv_plex ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_DETACH_PLEX ; 
 int /*<<< orphan*/  GV_EVENT_DETACH_SD ; 
#define  GV_TYPE_PLEX 129 
#define  GV_TYPE_SD 128 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct gv_sd* gv_find_plex (struct gv_softc*,char*) ; 
 struct gv_sd* gv_find_sd (struct gv_softc*,char*) ; 
 int gv_object_type (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_sd*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gv_detach(struct gv_softc *sc, struct gctl_req *req)
{
	struct gv_plex *p;
	struct gv_sd *s;
	int *flags, type;
	char *object;

	object = gctl_get_param(req, "object", NULL);
	if (object == NULL) {
		gctl_error(req, "no argument given");
		return;
	}

	flags = gctl_get_paraml(req, "flags", sizeof(*flags));
	type = gv_object_type(sc, object);
	switch (type) {
	case GV_TYPE_PLEX:
		p = gv_find_plex(sc, object);
		gv_post_event(sc, GV_EVENT_DETACH_PLEX, p, NULL, *flags, 0);
		break;
	case GV_TYPE_SD:
		s = gv_find_sd(sc, object);
		gv_post_event(sc, GV_EVENT_DETACH_SD, s, NULL, *flags, 0);
		break;
	default:
		gctl_error(req, "invalid object type");
		break;
	}
}