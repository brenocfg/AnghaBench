#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  jj_offset; } ;
struct g_journal_softc {int sc_flags; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_journal_previous_id; TYPE_1__ sc_inactive; int /*<<< orphan*/  sc_jend; int /*<<< orphan*/  sc_jstart; int /*<<< orphan*/  sc_orig_type; int /*<<< orphan*/  sc_id; struct g_consumer* sc_dconsumer; } ;
struct g_journal_metadata {scalar_t__ md_provsize; int /*<<< orphan*/  md_provider; int /*<<< orphan*/  md_flags; int /*<<< orphan*/  md_jid; int /*<<< orphan*/  md_joffset; int /*<<< orphan*/  md_jend; int /*<<< orphan*/  md_jstart; int /*<<< orphan*/  md_type; int /*<<< orphan*/  md_id; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
struct g_consumer {TYPE_2__* provider; } ;
struct bio {int /*<<< orphan*/  (* bio_done ) (struct bio*) ;int /*<<< orphan*/  bio_cmd; int /*<<< orphan*/ * bio_data; scalar_t__ bio_length; scalar_t__ bio_offset; } ;
struct TYPE_4__ {scalar_t__ sectorsize; scalar_t__ mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int GJF_DEVICE_CLEAN ; 
 int GJF_DEVICE_DESTROY ; 
 int GJF_DEVICE_HARDCODED ; 
 int /*<<< orphan*/  GJ_FLAG_CLEAN ; 
 int /*<<< orphan*/  G_JOURNAL_MAGIC ; 
 int /*<<< orphan*/  G_JOURNAL_VERSION ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  biowait (struct bio*,char*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_journal_flush_cache (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_metadata_done (struct bio*) ; 
 int /*<<< orphan*/ * gj_malloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_metadata_encode (struct g_journal_metadata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_journal_metadata_update(struct g_journal_softc *sc)
{
	struct g_journal_metadata md;
	struct g_consumer *cp;
	struct bio *bp;
	u_char *sector;

	cp = sc->sc_dconsumer;
	sector = gj_malloc(cp->provider->sectorsize, M_WAITOK);
	strlcpy(md.md_magic, G_JOURNAL_MAGIC, sizeof(md.md_magic));
	md.md_version = G_JOURNAL_VERSION;
	md.md_id = sc->sc_id;
	md.md_type = sc->sc_orig_type;
	md.md_jstart = sc->sc_jstart;
	md.md_jend = sc->sc_jend;
	md.md_joffset = sc->sc_inactive.jj_offset;
	md.md_jid = sc->sc_journal_previous_id;
	md.md_flags = 0;
	if (sc->sc_flags & GJF_DEVICE_CLEAN)
		md.md_flags |= GJ_FLAG_CLEAN;

	if (sc->sc_flags & GJF_DEVICE_HARDCODED)
		strlcpy(md.md_provider, sc->sc_name, sizeof(md.md_provider));
	else
		bzero(md.md_provider, sizeof(md.md_provider));
	md.md_provsize = cp->provider->mediasize;
	journal_metadata_encode(&md, sector);

	/*
	 * Flush the cache, so we know all data are on disk.
	 * We write here informations like "journal is consistent", so we need
	 * to be sure it is. Without BIO_FLUSH here, we can end up in situation
	 * where metadata is stored on disk, but not all data.
	 */
	g_journal_flush_cache(sc);

	bp = g_alloc_bio();
	bp->bio_offset = cp->provider->mediasize - cp->provider->sectorsize;
	bp->bio_length = cp->provider->sectorsize;
	bp->bio_data = sector;
	bp->bio_cmd = BIO_WRITE;
	if (!(sc->sc_flags & GJF_DEVICE_DESTROY)) {
		bp->bio_done = g_journal_metadata_done;
		g_io_request(bp, cp);
	} else {
		bp->bio_done = NULL;
		g_io_request(bp, cp);
		biowait(bp, "gjmdu");
		g_journal_metadata_done(bp);
	}

	/*
	 * Be sure metadata reached the disk.
	 */
	g_journal_flush_cache(sc);
}