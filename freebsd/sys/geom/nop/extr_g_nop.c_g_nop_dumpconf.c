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
struct g_provider {int dummy; } ;
struct g_nop_softc {int /*<<< orphan*/  sc_wrotebytes; int /*<<< orphan*/  sc_readbytes; int /*<<< orphan*/  sc_cmd2s; int /*<<< orphan*/  sc_cmd1s; int /*<<< orphan*/  sc_cmd0s; int /*<<< orphan*/  sc_flushes; int /*<<< orphan*/  sc_getattrs; int /*<<< orphan*/  sc_deletes; int /*<<< orphan*/  sc_writes; int /*<<< orphan*/  sc_reads; int /*<<< orphan*/  sc_error; int /*<<< orphan*/  sc_count_until_fail; int /*<<< orphan*/  sc_delaymsec; int /*<<< orphan*/  sc_wdelayprob; int /*<<< orphan*/  sc_rdelayprob; int /*<<< orphan*/  sc_wfailprob; int /*<<< orphan*/  sc_rfailprob; scalar_t__ sc_offset; } ;
struct g_geom {struct g_nop_softc* softc; } ;
struct g_consumer {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_nop_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_nop_softc *sc;

	if (pp != NULL || cp != NULL)
		return;
	sc = gp->softc;
	sbuf_printf(sb, "%s<Offset>%jd</Offset>\n", indent,
	    (intmax_t)sc->sc_offset);
	sbuf_printf(sb, "%s<ReadFailProb>%u</ReadFailProb>\n", indent,
	    sc->sc_rfailprob);
	sbuf_printf(sb, "%s<WriteFailProb>%u</WriteFailProb>\n", indent,
	    sc->sc_wfailprob);
	sbuf_printf(sb, "%s<ReadDelayedProb>%u</ReadDelayedProb>\n", indent,
	    sc->sc_rdelayprob);
	sbuf_printf(sb, "%s<WriteDelayedProb>%u</WriteDelayedProb>\n", indent,
	    sc->sc_wdelayprob);
	sbuf_printf(sb, "%s<Delay>%d</Delay>\n", indent, sc->sc_delaymsec);
	sbuf_printf(sb, "%s<CountUntilFail>%u</CountUntilFail>\n", indent,
	    sc->sc_count_until_fail);
	sbuf_printf(sb, "%s<Error>%d</Error>\n", indent, sc->sc_error);
	sbuf_printf(sb, "%s<Reads>%ju</Reads>\n", indent, sc->sc_reads);
	sbuf_printf(sb, "%s<Writes>%ju</Writes>\n", indent, sc->sc_writes);
	sbuf_printf(sb, "%s<Deletes>%ju</Deletes>\n", indent, sc->sc_deletes);
	sbuf_printf(sb, "%s<Getattrs>%ju</Getattrs>\n", indent, sc->sc_getattrs);
	sbuf_printf(sb, "%s<Flushes>%ju</Flushes>\n", indent, sc->sc_flushes);
	sbuf_printf(sb, "%s<Cmd0s>%ju</Cmd0s>\n", indent, sc->sc_cmd0s);
	sbuf_printf(sb, "%s<Cmd1s>%ju</Cmd1s>\n", indent, sc->sc_cmd1s);
	sbuf_printf(sb, "%s<Cmd2s>%ju</Cmd2s>\n", indent, sc->sc_cmd2s);
	sbuf_printf(sb, "%s<ReadBytes>%ju</ReadBytes>\n", indent,
	    sc->sc_readbytes);
	sbuf_printf(sb, "%s<WroteBytes>%ju</WroteBytes>\n", indent,
	    sc->sc_wrotebytes);
}