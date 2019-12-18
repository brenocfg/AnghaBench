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
struct sbuf {int dummy; } ;
struct gv_softc {int dummy; } ;
struct gctl_req {int dummy; } ;
struct g_geom {struct gv_softc* softc; } ;
struct g_class {int /*<<< orphan*/  geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_CFG_LEN ; 
 int /*<<< orphan*/  GV_EVENT_RESET_CONFIG ; 
 int /*<<< orphan*/  GV_EVENT_SAVE_CONFIG ; 
 struct g_geom* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gctl_set_param (struct gctl_req*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gv_attach (struct gv_softc*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_concat (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_create (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_detach (struct gv_softc*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_format_config (struct gv_softc*,struct sbuf*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gv_list (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_mirror (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_move (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_parityop (struct gv_softc*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_raid5 (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_remove (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_rename (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_setstate (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_start_obj (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  gv_stripe (struct g_geom*,struct gctl_req*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 scalar_t__ sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
gv_config(struct gctl_req *req, struct g_class *mp, char const *verb)
{
	struct g_geom *gp;
	struct gv_softc *sc;
	struct sbuf *sb;
	char *comment;

	g_topology_assert();

	gp = LIST_FIRST(&mp->geom);
	sc = gp->softc;

	if (!strcmp(verb, "attach")) {
		gv_attach(sc, req);

	} else if (!strcmp(verb, "concat")) {
		gv_concat(gp, req);

	} else if (!strcmp(verb, "detach")) {
		gv_detach(sc, req);

	} else if (!strcmp(verb, "list")) {
		gv_list(gp, req);

	/* Save our configuration back to disk. */
	} else if (!strcmp(verb, "saveconfig")) {
		gv_post_event(sc, GV_EVENT_SAVE_CONFIG, sc, NULL, 0, 0);

	/* Return configuration in string form. */
	} else if (!strcmp(verb, "getconfig")) {
		comment = gctl_get_param(req, "comment", NULL);
		if (comment == NULL) {
			gctl_error(req, "no comment parameter given");
			return;
		}
		sb = sbuf_new(NULL, NULL, GV_CFG_LEN, SBUF_FIXEDLEN);
		gv_format_config(sc, sb, 0, comment);
		sbuf_finish(sb);
		gctl_set_param(req, "config", sbuf_data(sb), sbuf_len(sb) + 1);
		sbuf_delete(sb);

	} else if (!strcmp(verb, "create")) {
		gv_create(gp, req);

	} else if (!strcmp(verb, "mirror")) {
		gv_mirror(gp, req);

	} else if (!strcmp(verb, "move")) {
		gv_move(gp, req);

	} else if (!strcmp(verb, "raid5")) {
		gv_raid5(gp, req);

	} else if (!strcmp(verb, "rebuildparity") ||
	    !strcmp(verb, "checkparity")) {
		gv_parityop(sc, req);

	} else if (!strcmp(verb, "remove")) {
		gv_remove(gp, req);

	} else if (!strcmp(verb, "rename")) {
		gv_rename(gp, req);
	
	} else if (!strcmp(verb, "resetconfig")) {
		gv_post_event(sc, GV_EVENT_RESET_CONFIG, sc, NULL, 0, 0);

	} else if (!strcmp(verb, "start")) {
		gv_start_obj(gp, req);

	} else if (!strcmp(verb, "stripe")) {
		gv_stripe(gp, req);

	} else if (!strcmp(verb, "setstate")) {
		gv_setstate(gp, req);
	} else
		gctl_error(req, "Unknown verb parameter");
}