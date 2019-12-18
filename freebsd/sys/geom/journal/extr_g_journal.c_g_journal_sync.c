#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {scalar_t__ jj_offset; struct bio* jj_queue; } ;
struct TYPE_4__ {scalar_t__ jj_offset; } ;
struct g_journal_softc {scalar_t__ sc_journal_offset; scalar_t__ sc_journal_id; scalar_t__ sc_journal_next_id; int sc_flags; int /*<<< orphan*/  sc_name; TYPE_2__ sc_inactive; TYPE_1__ sc_active; struct g_consumer* sc_jconsumer; } ;
struct g_journal_record_header {int jrh_nentries; int /*<<< orphan*/  jrh_sum; struct g_journal_entry* jrh_entries; } ;
struct g_journal_header {scalar_t__ jh_journal_id; scalar_t__ jh_journal_next_id; } ;
struct g_journal_entry {scalar_t__ je_offset; scalar_t__ je_length; int /*<<< orphan*/  je_joffset; } ;
struct g_consumer {TYPE_3__* provider; } ;
struct bio {struct bio* bio_next; int /*<<< orphan*/  bio_data; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_6__ {scalar_t__ sectorsize; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int ENOENT ; 
 int GJF_DEVICE_CHECKSUM ; 
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  GJ_VALIDATE_OFFSET (scalar_t__,struct g_journal_softc*) ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_journal_copy_start (struct g_journal_softc*) ; 
 int g_journal_header_decode (int /*<<< orphan*/ *,struct g_journal_header*) ; 
 int /*<<< orphan*/  g_journal_initialize (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_insert (struct bio**,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_journal_insert_bio (struct bio**,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_journal_mark_as_dirty (struct g_journal_softc*) ; 
 int g_journal_record_header_decode (int /*<<< orphan*/ *,struct g_journal_record_header*) ; 
 int g_journal_sync_read (struct g_consumer*,struct bio*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gj_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * gj_malloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_journal_sync(struct g_journal_softc *sc)
{
	struct g_journal_record_header rhdr;
	struct g_journal_entry *ent;
	struct g_journal_header jhdr;
	struct g_consumer *cp;
	struct bio *bp, *fbp, *tbp;
	off_t joffset, offset;
	u_char *buf, sum[16];
	uint64_t id;
	MD5_CTX ctx;
	int error, found, i;

	found = 0;
	fbp = NULL;
	cp = sc->sc_jconsumer;
	bp = g_alloc_bio();
	buf = gj_malloc(cp->provider->sectorsize, M_WAITOK);
	offset = joffset = sc->sc_inactive.jj_offset = sc->sc_journal_offset;

	GJ_DEBUG(2, "Looking for termination at %jd.", (intmax_t)joffset);

	/*
	 * Read and decode first journal header.
	 */
	error = g_journal_sync_read(cp, bp, offset, buf);
	if (error != 0) {
		GJ_DEBUG(0, "Error while reading journal header from %s.",
		    cp->provider->name);
		goto end;
	}
	error = g_journal_header_decode(buf, &jhdr);
	if (error != 0) {
		GJ_DEBUG(0, "Cannot decode journal header from %s.",
		    cp->provider->name);
		goto end;
	}
	id = sc->sc_journal_id;
	if (jhdr.jh_journal_id != sc->sc_journal_id) {
		GJ_DEBUG(1, "Journal ID mismatch at %jd (0x%08x != 0x%08x).",
		    (intmax_t)offset, (u_int)jhdr.jh_journal_id, (u_int)id);
		goto end;
	}
	offset += cp->provider->sectorsize;
	id = sc->sc_journal_next_id = jhdr.jh_journal_next_id;

	for (;;) {
		/*
		 * If the biggest record won't fit, look for a record header or
		 * journal header from the beginning.
		 */
		GJ_VALIDATE_OFFSET(offset, sc);
		error = g_journal_sync_read(cp, bp, offset, buf);
		if (error != 0) {
			/*
			 * Not good. Having an error while reading header
			 * means, that we cannot read next headers and in
			 * consequence we cannot find termination.
			 */
			GJ_DEBUG(0,
			    "Error while reading record header from %s.",
			    cp->provider->name);
			break;
		}

		error = g_journal_record_header_decode(buf, &rhdr);
		if (error != 0) {
			GJ_DEBUG(2, "Not a record header at %jd (error=%d).",
			    (intmax_t)offset, error);
			/*
			 * This is not a record header.
			 * If we are lucky, this is next journal header.
			 */
			error = g_journal_header_decode(buf, &jhdr);
			if (error != 0) {
				GJ_DEBUG(1, "Not a journal header at %jd (error=%d).",
				    (intmax_t)offset, error);
				/*
				 * Nope, this is not journal header, which
				 * bascially means that journal is not
				 * terminated properly.
				 */
				error = ENOENT;
				break;
			}
			/*
			 * Ok. This is header of _some_ journal. Now we need to
			 * verify if this is header of the _next_ journal.
			 */
			if (jhdr.jh_journal_id != id) {
				GJ_DEBUG(1, "Journal ID mismatch at %jd "
				    "(0x%08x != 0x%08x).", (intmax_t)offset,
				    (u_int)jhdr.jh_journal_id, (u_int)id);
				error = ENOENT;
				break;
			}

			/* Found termination. */
			found++;
			GJ_DEBUG(1, "Found termination at %jd (id=0x%08x).",
			    (intmax_t)offset, (u_int)id);
			sc->sc_active.jj_offset = offset;
			sc->sc_journal_offset =
			    offset + cp->provider->sectorsize;
			sc->sc_journal_id = id;
			id = sc->sc_journal_next_id = jhdr.jh_journal_next_id;

			while ((tbp = fbp) != NULL) {
				fbp = tbp->bio_next;
				GJ_LOGREQ(3, tbp, "Adding request.");
				g_journal_insert_bio(&sc->sc_inactive.jj_queue,
				    tbp, M_WAITOK);
			}

			/* Skip journal's header. */
			offset += cp->provider->sectorsize;
			continue;
		}

		/* Skip record's header. */
		offset += cp->provider->sectorsize;

		/*
		 * Add information about every record entry to the inactive
		 * queue.
		 */
		if (sc->sc_flags & GJF_DEVICE_CHECKSUM)
			MD5Init(&ctx);
		for (i = 0; i < rhdr.jrh_nentries; i++) {
			ent = &rhdr.jrh_entries[i];
			GJ_DEBUG(3, "Insert entry: %jd %jd.",
			    (intmax_t)ent->je_offset, (intmax_t)ent->je_length);
			g_journal_insert(&fbp, ent->je_offset,
			    ent->je_offset + ent->je_length, ent->je_joffset,
			    NULL, M_WAITOK);
			if (sc->sc_flags & GJF_DEVICE_CHECKSUM) {
				u_char *buf2;

				/*
				 * TODO: Should use faster function (like
				 *       g_journal_sync_read()).
				 */
				buf2 = g_read_data(cp, offset, ent->je_length,
				    NULL);
				if (buf2 == NULL)
					GJ_DEBUG(0, "Cannot read data at %jd.",
					    (intmax_t)offset);
				else {
					MD5Update(&ctx, buf2, ent->je_length);
					g_free(buf2);
				}
			}
			/* Skip entry's data. */
			offset += ent->je_length;
		}
		if (sc->sc_flags & GJF_DEVICE_CHECKSUM) {
			MD5Final(sum, &ctx);
			if (bcmp(sum, rhdr.jrh_sum, sizeof(rhdr.jrh_sum)) != 0) {
				GJ_DEBUG(0, "MD5 hash mismatch at %jd!",
				    (intmax_t)offset);
			}
		}
	}
end:
	gj_free(bp->bio_data, cp->provider->sectorsize);
	g_destroy_bio(bp);

	/* Remove bios from unterminated journal. */
	while ((tbp = fbp) != NULL) {
		fbp = tbp->bio_next;
		g_destroy_bio(tbp);
	}

	if (found < 1 && joffset > 0) {
		GJ_DEBUG(0, "Journal on %s is broken/corrupted. Initializing.",
		    sc->sc_name);
		while ((tbp = sc->sc_inactive.jj_queue) != NULL) {
			sc->sc_inactive.jj_queue = tbp->bio_next;
			g_destroy_bio(tbp);
		}
		g_journal_initialize(sc);
		g_journal_mark_as_dirty(sc);
	} else {
		GJ_DEBUG(0, "Journal %s consistent.", sc->sc_name);
		g_journal_copy_start(sc);
	}
}