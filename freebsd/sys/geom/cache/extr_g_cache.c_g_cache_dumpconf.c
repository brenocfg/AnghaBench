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
typedef  int /*<<< orphan*/  uintmax_t ;
struct sbuf {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_geom {struct g_cache_softc* softc; } ;
struct g_consumer {int dummy; } ;
struct g_cache_softc {int /*<<< orphan*/  sc_wrotebytes; int /*<<< orphan*/  sc_writes; int /*<<< orphan*/  sc_cachefull; int /*<<< orphan*/  sc_cachemisses; int /*<<< orphan*/  sc_cachehits; int /*<<< orphan*/  sc_cachereadbytes; int /*<<< orphan*/  sc_cachereads; int /*<<< orphan*/  sc_readbytes; int /*<<< orphan*/  sc_reads; int /*<<< orphan*/  sc_invalid; int /*<<< orphan*/  sc_nused; int /*<<< orphan*/  sc_nent; scalar_t__ sc_tail; int /*<<< orphan*/  sc_bsize; int /*<<< orphan*/  sc_maxent; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_cache_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp,
    struct g_consumer *cp, struct g_provider *pp)
{
	struct g_cache_softc *sc;

	if (pp != NULL || cp != NULL)
		return;
	sc = gp->softc;
	sbuf_printf(sb, "%s<Size>%u</Size>\n", indent, sc->sc_maxent);
	sbuf_printf(sb, "%s<BlockSize>%u</BlockSize>\n", indent, sc->sc_bsize);
	sbuf_printf(sb, "%s<TailOffset>%ju</TailOffset>\n", indent,
	    (uintmax_t)sc->sc_tail);
	sbuf_printf(sb, "%s<Entries>%u</Entries>\n", indent, sc->sc_nent);
	sbuf_printf(sb, "%s<UsedEntries>%u</UsedEntries>\n", indent,
	    sc->sc_nused);
	sbuf_printf(sb, "%s<InvalidEntries>%u</InvalidEntries>\n", indent,
	    sc->sc_invalid);
	sbuf_printf(sb, "%s<Reads>%ju</Reads>\n", indent, sc->sc_reads);
	sbuf_printf(sb, "%s<ReadBytes>%ju</ReadBytes>\n", indent,
	    sc->sc_readbytes);
	sbuf_printf(sb, "%s<CacheReads>%ju</CacheReads>\n", indent,
	    sc->sc_cachereads);
	sbuf_printf(sb, "%s<CacheReadBytes>%ju</CacheReadBytes>\n", indent,
	    sc->sc_cachereadbytes);
	sbuf_printf(sb, "%s<CacheHits>%ju</CacheHits>\n", indent,
	    sc->sc_cachehits);
	sbuf_printf(sb, "%s<CacheMisses>%ju</CacheMisses>\n", indent,
	    sc->sc_cachemisses);
	sbuf_printf(sb, "%s<CacheFull>%ju</CacheFull>\n", indent,
	    sc->sc_cachefull);
	sbuf_printf(sb, "%s<Writes>%ju</Writes>\n", indent, sc->sc_writes);
	sbuf_printf(sb, "%s<WroteBytes>%ju</WroteBytes>\n", indent,
	    sc->sc_wrotebytes);
}