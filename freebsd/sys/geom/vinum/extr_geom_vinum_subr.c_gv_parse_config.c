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
struct gv_volume {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct gv_softc {int dummy; } ;
struct gv_sd {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct gv_plex {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct gv_drive {int dummy; } ;

/* Variables and functions */
 int GV_MAXARGS ; 
 int /*<<< orphan*/  GV_PLEX_ADDED ; 
 int /*<<< orphan*/  GV_SD_CANGOUP ; 
 int /*<<< orphan*/  GV_SD_GROW ; 
 int /*<<< orphan*/  GV_SD_NEWBORN ; 
 int /*<<< orphan*/  GV_SD_TASTED ; 
 scalar_t__ GV_SD_UP ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*) ; 
 int /*<<< orphan*/  g_free (struct gv_volume*) ; 
 int gv_create_plex (struct gv_softc*,struct gv_volume*) ; 
 int gv_create_sd (struct gv_softc*,struct gv_volume*) ; 
 int /*<<< orphan*/  gv_create_volume (struct gv_softc*,struct gv_volume*) ; 
 int gv_drive_is_newer (struct gv_softc*,struct gv_drive*) ; 
 struct gv_volume* gv_find_plex (struct gv_softc*,int /*<<< orphan*/ ) ; 
 struct gv_volume* gv_find_sd (struct gv_softc*,int /*<<< orphan*/ ) ; 
 struct gv_volume* gv_find_vol (struct gv_softc*,int /*<<< orphan*/ ) ; 
 struct gv_volume* gv_new_plex (int,char**) ; 
 struct gv_volume* gv_new_sd (int,char**) ; 
 struct gv_volume* gv_new_volume (int,char**) ; 
 int gv_tokenize (char*,char**,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
gv_parse_config(struct gv_softc *sc, char *buf, struct gv_drive *d)
{
	char *aptr, *bptr, *cptr;
	struct gv_volume *v, *v2;
	struct gv_plex *p, *p2;
	struct gv_sd *s, *s2;
	int error, is_newer, tokens;
	char *token[GV_MAXARGS];

	is_newer = gv_drive_is_newer(sc, d);

	/* Until the end of the string *buf. */
	for (aptr = buf; *aptr != '\0'; aptr = bptr) {
		bptr = aptr;
		cptr = aptr;

		/* Separate input lines. */
		while (*bptr != '\n')
			bptr++;
		*bptr = '\0';
		bptr++;

		tokens = gv_tokenize(cptr, token, GV_MAXARGS);

		if (tokens <= 0)
			continue;

		if (!strcmp(token[0], "volume")) {
			v = gv_new_volume(tokens, token);
			if (v == NULL) {
				G_VINUM_DEBUG(0, "config parse failed volume");
				break;
			}

			v2 = gv_find_vol(sc, v->name);
			if (v2 != NULL) {
				if (is_newer) {
					v2->state = v->state;
					G_VINUM_DEBUG(2, "newer volume found!");
				}
				g_free(v);
				continue;
			}

			gv_create_volume(sc, v);

		} else if (!strcmp(token[0], "plex")) {
			p = gv_new_plex(tokens, token);
			if (p == NULL) {
				G_VINUM_DEBUG(0, "config parse failed plex");
				break;
			}

			p2 = gv_find_plex(sc, p->name);
			if (p2 != NULL) {
				/* XXX */
				if (is_newer) {
					p2->state = p->state;
					G_VINUM_DEBUG(2, "newer plex found!");
				}
				g_free(p);
				continue;
			}

			error = gv_create_plex(sc, p);
			if (error)
				continue;
			/*
			 * These flags were set in gv_create_plex() and are not
			 * needed here (on-disk config parsing).
			 */
			p->flags &= ~GV_PLEX_ADDED;

		} else if (!strcmp(token[0], "sd")) {
			s = gv_new_sd(tokens, token);

			if (s == NULL) {
				G_VINUM_DEBUG(0, "config parse failed subdisk");
				break;
			}

			s2 = gv_find_sd(sc, s->name);
			if (s2 != NULL) {
				/* XXX */
				if (is_newer) {
					s2->state = s->state;
					G_VINUM_DEBUG(2, "newer subdisk found!");
				}
				g_free(s);
				continue;
			}

			/*
			 * Signal that this subdisk was tasted, and could
			 * possibly reference a drive that isn't in our config
			 * yet.
			 */
			s->flags |= GV_SD_TASTED;

			if (s->state == GV_SD_UP)
				s->flags |= GV_SD_CANGOUP;

			error = gv_create_sd(sc, s);
			if (error)
				continue;

			/*
			 * This flag was set in gv_create_sd() and is not
			 * needed here (on-disk config parsing).
			 */
			s->flags &= ~GV_SD_NEWBORN;
			s->flags &= ~GV_SD_GROW;
		}
	}
}