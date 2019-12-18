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
struct gv_plex {scalar_t__ state; char* name; scalar_t__ org; } ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_PARITY_CHECK ; 
 int /*<<< orphan*/  GV_EVENT_PARITY_REBUILD ; 
 scalar_t__ GV_PLEX_RAID5 ; 
 scalar_t__ GV_PLEX_UP ; 
 int GV_TYPE_PLEX ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 struct gv_plex* gv_find_plex (struct gv_softc*,char*) ; 
 int gv_object_type (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_plex*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gv_parityop(struct gv_softc *sc, struct gctl_req *req)
{
	struct gv_plex *p;
	int *flags, *rebuild, type;
	char *plex;

	plex = gctl_get_param(req, "plex", NULL);
	if (plex == NULL) {
		gctl_error(req, "no plex given");
		return;
	}

	flags = gctl_get_paraml(req, "flags", sizeof(*flags));
	if (flags == NULL) {
		gctl_error(req, "no flags given");
		return;
	}

	rebuild = gctl_get_paraml(req, "rebuild", sizeof(*rebuild));
	if (rebuild == NULL) {
		gctl_error(req, "no operation given");
		return;
	}

	type = gv_object_type(sc, plex);
	if (type != GV_TYPE_PLEX) {
		gctl_error(req, "'%s' is not a plex", plex);
		return;
	}
	p = gv_find_plex(sc, plex);

	if (p->state != GV_PLEX_UP) {
		gctl_error(req, "plex %s is not completely accessible",
		    p->name);
		return;
	}

	if (p->org != GV_PLEX_RAID5) {
		gctl_error(req, "plex %s is not a RAID5 plex", p->name);
		return;
	}

	/* Put it in the event queue. */
	/* XXX: The state of the plex might have changed when this event is
	 * picked up ... We should perhaps check this afterwards. */
	if (*rebuild)
		gv_post_event(sc, GV_EVENT_PARITY_REBUILD, p, NULL, 0, 0);
	else
		gv_post_event(sc, GV_EVENT_PARITY_CHECK, p, NULL, 0, 0);
}