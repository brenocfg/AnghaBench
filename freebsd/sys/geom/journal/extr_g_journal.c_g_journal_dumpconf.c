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
typedef  int /*<<< orphan*/  u_int ;
struct sbuf {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_journal_softc {scalar_t__ sc_id; scalar_t__ sc_jend; scalar_t__ sc_jstart; struct g_consumer* sc_jconsumer; struct g_consumer* sc_dconsumer; } ;
struct g_geom {struct g_journal_softc* softc; } ;
struct g_consumer {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 

__attribute__((used)) static void
g_journal_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_journal_softc *sc;

	g_topology_assert();

	sc = gp->softc;
	if (sc == NULL)
		return;
	if (pp != NULL) {
		/* Nothing here. */
	} else if (cp != NULL) {
		int first = 1;

		sbuf_printf(sb, "%s<Role>", indent);
		if (cp == sc->sc_dconsumer) {
			sbuf_cat(sb, "Data");
			first = 0;
		}
		if (cp == sc->sc_jconsumer) {
			if (!first)
				sbuf_cat(sb, ",");
			sbuf_cat(sb, "Journal");
		}
		sbuf_cat(sb, "</Role>\n");
		if (cp == sc->sc_jconsumer) {
			sbuf_printf(sb, "<Jstart>%jd</Jstart>\n",
			    (intmax_t)sc->sc_jstart);
			sbuf_printf(sb, "<Jend>%jd</Jend>\n",
			    (intmax_t)sc->sc_jend);
		}
	} else {
		sbuf_printf(sb, "%s<ID>%u</ID>\n", indent, (u_int)sc->sc_id);
	}
}