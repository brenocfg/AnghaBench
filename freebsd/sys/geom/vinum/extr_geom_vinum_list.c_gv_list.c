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
struct gv_volume {int dummy; } ;
struct gv_softc {int dummy; } ;
struct gv_sd {int dummy; } ;
struct gv_plex {int dummy; } ;
struct gv_drive {int dummy; } ;
struct gctl_req {int dummy; } ;
struct g_geom {struct gv_softc* softc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GV_CFG_LEN ; 
#define  GV_TYPE_DRIVE 131 
#define  GV_TYPE_PLEX 130 
#define  GV_TYPE_SD 129 
#define  GV_TYPE_VOL 128 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_param (struct gctl_req*,char*,int /*<<< orphan*/ *) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  gctl_set_param (struct gctl_req*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct gv_drive* gv_find_drive (struct gv_softc*,char*) ; 
 struct gv_plex* gv_find_plex (struct gv_softc*,char*) ; 
 struct gv_sd* gv_find_sd (struct gv_softc*,char*) ; 
 struct gv_volume* gv_find_vol (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  gv_ld (struct g_geom*,struct gctl_req*,struct sbuf*) ; 
 int /*<<< orphan*/  gv_ldi (struct gv_drive*,struct sbuf*,int) ; 
 int /*<<< orphan*/  gv_lp (struct g_geom*,struct gctl_req*,struct sbuf*) ; 
 int /*<<< orphan*/  gv_lpi (struct gv_plex*,struct sbuf*,int) ; 
 int /*<<< orphan*/  gv_ls (struct g_geom*,struct gctl_req*,struct sbuf*) ; 
 int /*<<< orphan*/  gv_lsi (struct gv_sd*,struct sbuf*,int) ; 
 int /*<<< orphan*/  gv_lv (struct g_geom*,struct gctl_req*,struct sbuf*) ; 
 int /*<<< orphan*/  gv_lvi (struct gv_volume*,struct sbuf*,int) ; 
 int gv_object_type (struct gv_softc*,char*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 scalar_t__ sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
gv_list(struct g_geom *gp, struct gctl_req *req)
{
	struct gv_softc *sc;
	struct gv_drive *d;
	struct gv_plex *p;
	struct gv_sd *s;
	struct gv_volume *v;
	struct sbuf *sb;
	int *argc, i, *flags, type;
	char *arg, buf[20], *cmd;

	argc = gctl_get_paraml(req, "argc", sizeof(*argc));

	if (argc == NULL) {
		gctl_error(req, "no arguments given");
		return;
	}

	flags = gctl_get_paraml(req, "flags", sizeof(*flags));
	if (flags == NULL) {
		gctl_error(req, "no flags given");
		return;
	}

	sc = gp->softc;

	sb = sbuf_new(NULL, NULL, GV_CFG_LEN, SBUF_FIXEDLEN);

	/* Figure out which command was given. */
	cmd = gctl_get_param(req, "cmd", NULL);
	if (cmd == NULL) {
		gctl_error(req, "no command given");
		return;
	}

	/* List specific objects or everything. */
	if (!strcmp(cmd, "list") || !strcmp(cmd, "l")) {
		if (*argc) {
			for (i = 0; i < *argc; i++) {
				snprintf(buf, sizeof(buf), "argv%d", i);
				arg = gctl_get_param(req, buf, NULL);
				if (arg == NULL)
					continue;
				type = gv_object_type(sc, arg);
				switch (type) {
				case GV_TYPE_VOL:
					v = gv_find_vol(sc, arg);
					gv_lvi(v, sb, *flags);
					break;
				case GV_TYPE_PLEX:
					p = gv_find_plex(sc, arg);
					gv_lpi(p, sb, *flags);
					break;
				case GV_TYPE_SD:
					s = gv_find_sd(sc, arg);
					gv_lsi(s, sb, *flags);
					break;
				case GV_TYPE_DRIVE:
					d = gv_find_drive(sc, arg);
					gv_ldi(d, sb, *flags);
					break;
				default:
					gctl_error(req, "unknown object '%s'",
					    arg);
					break;
				}
			}
		} else {
			gv_ld(gp, req, sb);
			sbuf_printf(sb, "\n");
			gv_lv(gp, req, sb);
			sbuf_printf(sb, "\n");
			gv_lp(gp, req, sb);
			sbuf_printf(sb, "\n");
			gv_ls(gp, req, sb);
		}

	/* List drives. */
	} else if (!strcmp(cmd, "ld")) {
		if (*argc) {
			for (i = 0; i < *argc; i++) {
				snprintf(buf, sizeof(buf), "argv%d", i);
				arg = gctl_get_param(req, buf, NULL);
				if (arg == NULL)
					continue;
				type = gv_object_type(sc, arg);
				if (type != GV_TYPE_DRIVE) {
					gctl_error(req, "'%s' is not a drive",
					    arg);
					continue;
				} else {
					d = gv_find_drive(sc, arg);
					gv_ldi(d, sb, *flags);
				}
			}
		} else
			gv_ld(gp, req, sb);

	/* List volumes. */
	} else if (!strcmp(cmd, "lv")) {
		if (*argc) {
			for (i = 0; i < *argc; i++) {
				snprintf(buf, sizeof(buf), "argv%d", i);
				arg = gctl_get_param(req, buf, NULL);
				if (arg == NULL)
					continue;
				type = gv_object_type(sc, arg);
				if (type != GV_TYPE_VOL) {
					gctl_error(req, "'%s' is not a volume",
					    arg);
					continue;
				} else {
					v = gv_find_vol(sc, arg);
					gv_lvi(v, sb, *flags);
				}
			}
		} else
			gv_lv(gp, req, sb);

	/* List plexes. */
	} else if (!strcmp(cmd, "lp")) {
		if (*argc) {
			for (i = 0; i < *argc; i++) {
				snprintf(buf, sizeof(buf), "argv%d", i);
				arg = gctl_get_param(req, buf, NULL);
				if (arg == NULL)
					continue;
				type = gv_object_type(sc, arg);
				if (type != GV_TYPE_PLEX) {
					gctl_error(req, "'%s' is not a plex",
					    arg);
					continue;
				} else {
					p = gv_find_plex(sc, arg);
					gv_lpi(p, sb, *flags);
				}
			}
		} else
			gv_lp(gp, req, sb);

	/* List subdisks. */
	} else if (!strcmp(cmd, "ls")) {
		if (*argc) {
			for (i = 0; i < *argc; i++) {
				snprintf(buf, sizeof(buf), "argv%d", i);
				arg = gctl_get_param(req, buf, NULL);
				if (arg == NULL)
					continue;
				type = gv_object_type(sc, arg);
				if (type != GV_TYPE_SD) {
					gctl_error(req, "'%s' is not a subdisk",
					    arg);
					continue;
				} else {
					s = gv_find_sd(sc, arg);
					gv_lsi(s, sb, *flags);
				}
			}
		} else
			gv_ls(gp, req, sb);

	} else
		gctl_error(req, "unknown command '%s'", cmd);

	sbuf_finish(sb);
	gctl_set_param(req, "config", sbuf_data(sb), sbuf_len(sb) + 1);
	sbuf_delete(sb);
}