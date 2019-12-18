#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct g_journal_softc {int /*<<< orphan*/  sc_journal_offset; int /*<<< orphan*/  sc_journal_next_id; int /*<<< orphan*/  sc_journal_id; struct g_consumer* sc_jconsumer; } ;
struct g_journal_header {int /*<<< orphan*/  jh_journal_next_id; int /*<<< orphan*/  jh_journal_id; int /*<<< orphan*/  jh_magic; } ;
struct g_consumer {TYPE_1__* provider; } ;
struct TYPE_2__ {scalar_t__ sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_HEADER_MAGIC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  g_journal_header_encode (struct g_journal_header*,int /*<<< orphan*/ *) ; 
 int g_write_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gj_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * gj_malloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
g_journal_write_header(struct g_journal_softc *sc)
{
	struct g_journal_header hdr;
	struct g_consumer *cp;
	u_char *buf;
	int error;

	cp = sc->sc_jconsumer;
	buf = gj_malloc(cp->provider->sectorsize, M_WAITOK);

	strlcpy(hdr.jh_magic, GJ_HEADER_MAGIC, sizeof(hdr.jh_magic));
	hdr.jh_journal_id = sc->sc_journal_id;
	hdr.jh_journal_next_id = sc->sc_journal_next_id;
	g_journal_header_encode(&hdr, buf);
	error = g_write_data(cp, sc->sc_journal_offset, buf,
	    cp->provider->sectorsize);
	/* if (error == 0) */
	sc->sc_journal_offset += cp->provider->sectorsize;

	gj_free(buf, cp->provider->sectorsize);
	return (error);
}