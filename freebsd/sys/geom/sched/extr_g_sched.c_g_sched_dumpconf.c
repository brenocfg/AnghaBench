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
struct g_sched_softc {struct g_gsched* sc_gsched; } ;
struct g_provider {int dummy; } ;
struct g_gsched {char* gs_name; int /*<<< orphan*/  (* gs_dumpconf ) (struct sbuf*,char const*,struct g_geom*,struct g_consumer*,struct g_provider*) ;} ;
struct g_geom {struct g_sched_softc* softc; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct sbuf*,char const*,struct g_geom*,struct g_consumer*,struct g_provider*) ; 

__attribute__((used)) static void
g_sched_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_sched_softc *sc = gp->softc;
	struct g_gsched *gsp = sc->sc_gsched;
	if (indent == NULL) {	/* plaintext */
		sbuf_printf(sb, " algo %s", gsp ? gsp->gs_name : "--");
	}
	if (gsp != NULL && gsp->gs_dumpconf)
		gsp->gs_dumpconf(sb, indent, gp, cp, pp);
}