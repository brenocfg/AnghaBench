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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct g_uzip_softc {int nblocks; struct g_uzip_blk* toc; TYPE_1__* dcp; int /*<<< orphan*/  blksz; } ;
struct g_uzip_blk {int offset; int blen; int last; int padded; } ;
struct g_provider {int mediasize; } ;
struct g_geom {int /*<<< orphan*/  name; } ;
struct cloop_header {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_2__ {int max_blen; } ;

/* Variables and functions */
 size_t BLEN_UNDEF ; 
 int BLK_ENDS (struct g_uzip_softc*,size_t) ; 
 int /*<<< orphan*/  BLK_IS_NIL (struct g_uzip_softc*,size_t) ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DPRINTF_BLK (int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  GUZ_DBG_ERR ; 
 int /*<<< orphan*/  GUZ_DBG_INFO ; 
 int /*<<< orphan*/  GUZ_DBG_IO ; 
 int /*<<< orphan*/  GUZ_DBG_TOC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static int
g_uzip_parse_toc(struct g_uzip_softc *sc, struct g_provider *pp,
    struct g_geom *gp)
{
	uint32_t i, j, backref_to;
	uint64_t max_offset, min_offset;
	struct g_uzip_blk *last_blk;

	min_offset = sizeof(struct cloop_header) +
	    (sc->nblocks + 1) * sizeof(uint64_t);
	max_offset = sc->toc[0].offset - 1;
	last_blk = &sc->toc[0];
	for (i = 0; i < sc->nblocks; i++) {
		/* First do some bounds checking */
		if ((sc->toc[i].offset < min_offset) ||
		    (sc->toc[i].offset > pp->mediasize)) {
			goto error_offset;
		}
		DPRINTF_BLK(GUZ_DBG_IO, i, ("%s: cluster #%u "
		    "offset=%ju max_offset=%ju\n", gp->name,
		    (u_int)i, (uintmax_t)sc->toc[i].offset,
		    (uintmax_t)max_offset));
		backref_to = BLEN_UNDEF;
		if (sc->toc[i].offset < max_offset) {
			/*
			 * For the backref'ed blocks search already parsed
			 * TOC entries for the matching offset and copy the
			 * size from matched entry.
			 */
			for (j = 0; j <= i; j++) {
                                if (sc->toc[j].offset == sc->toc[i].offset &&
				    !BLK_IS_NIL(sc, j)) {
                                        break;
                                }
                                if (j != i) {
					continue;
				}
				DPRINTF(GUZ_DBG_ERR, ("%s: cannot match "
				    "backref'ed offset at cluster #%u\n",
				    gp->name, i));
				return (-1);
			}
			sc->toc[i].blen = sc->toc[j].blen;
			backref_to = j;
		} else {
			last_blk = &sc->toc[i];
			/*
			 * For the "normal blocks" seek forward until we hit
			 * block whose offset is larger than ours and assume
			 * it's going to be the next one.
			 */
			for (j = i + 1; j < sc->nblocks + 1; j++) {
				if (sc->toc[j].offset > max_offset) {
					break;
				}
			}
			sc->toc[i].blen = sc->toc[j].offset -
			    sc->toc[i].offset;
			if (BLK_ENDS(sc, i) > pp->mediasize) {
				DPRINTF(GUZ_DBG_ERR, ("%s: cluster #%u "
				    "extends past media boundary (%ju > %ju)\n",
				    gp->name, (u_int)i,
				    (uintmax_t)BLK_ENDS(sc, i),
				    (intmax_t)pp->mediasize));
				return (-1);
			}
			KASSERT(max_offset <= sc->toc[i].offset, (
			    "%s: max_offset is incorrect: %ju",
			    gp->name, (uintmax_t)max_offset));
			max_offset = BLK_ENDS(sc, i) - 1;
		}
		DPRINTF_BLK(GUZ_DBG_TOC, i, ("%s: cluster #%u, original %u "
		    "bytes, in %u bytes", gp->name, i, sc->blksz,
		    sc->toc[i].blen));
		if (backref_to != BLEN_UNDEF) {
			DPRINTF_BLK(GUZ_DBG_TOC, i, (" (->#%u)",
			    (u_int)backref_to));
		}
		DPRINTF_BLK(GUZ_DBG_TOC, i, ("\n"));
	}
	last_blk->last = 1;
	/* Do a second pass to validate block lengths */
	for (i = 0; i < sc->nblocks; i++) {
		if (sc->toc[i].blen > sc->dcp->max_blen) {
			if (sc->toc[i].last == 0) {
				DPRINTF(GUZ_DBG_ERR, ("%s: cluster #%u "
				    "length (%ju) exceeds "
				    "max_blen (%ju)\n", gp->name, i,
				    (uintmax_t)sc->toc[i].blen,
				    (uintmax_t)sc->dcp->max_blen));
				return (-1);
			}
			DPRINTF(GUZ_DBG_INFO, ("%s: cluster #%u extra "
			    "padding is detected, trimmed to %ju\n",
			    gp->name, i, (uintmax_t)sc->dcp->max_blen));
			    sc->toc[i].blen = sc->dcp->max_blen;
			sc->toc[i].padded = 1;
		}
	}
	return (0);

error_offset:
	DPRINTF(GUZ_DBG_ERR, ("%s: cluster #%u: invalid offset %ju, "
	    "min_offset=%ju mediasize=%jd\n", gp->name, (u_int)i,
	    sc->toc[i].offset, min_offset, pp->mediasize));
	return (-1);
}