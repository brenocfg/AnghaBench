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
struct ccdiinfo {int ii_ndisk; scalar_t__ ii_startblk; int* ii_index; int ii_startoff; } ;
struct ccdcinfo {scalar_t__ ci_size; int /*<<< orphan*/  ci_consumer; } ;
struct ccd_s {scalar_t__ sc_ileave; int sc_flags; long sc_offset; struct ccdcinfo* sc_cinfo; struct ccdiinfo* sc_itable; } ;
struct bio {long bio_length; struct bio* bio_caller1; int /*<<< orphan*/  bio_from; int /*<<< orphan*/  bio_data; void* bio_offset; int /*<<< orphan*/  bio_done; } ;
typedef  long off_t ;
typedef  scalar_t__ daddr_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int CCDF_MIRROR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ccdiodone ; 
 void* dbtob (long) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_std_done ; 

__attribute__((used)) static int
ccdbuffer(struct bio **cb, struct ccd_s *cs, struct bio *bp, daddr_t bn, caddr_t addr, long bcount)
{
	struct ccdcinfo *ci, *ci2 = NULL;
	struct bio *cbp;
	daddr_t cbn, cboff;
	off_t cbc;

	/*
	 * Determine which component bn falls in.
	 */
	cbn = bn;
	cboff = 0;

	if (cs->sc_ileave == 0) {
		/*
		 * Serially concatenated and neither a mirror nor a parity
		 * config.  This is a special case.
		 */
		daddr_t sblk;

		sblk = 0;
		for (ci = cs->sc_cinfo; cbn >= sblk + ci->ci_size; ci++)
			sblk += ci->ci_size;
		cbn -= sblk;
	} else {
		struct ccdiinfo *ii;
		int ccdisk, off;

		/*
		 * Calculate cbn, the logical superblock (sc_ileave chunks),
		 * and cboff, a normal block offset (DEV_BSIZE chunks) relative
		 * to cbn.
		 */
		cboff = cbn % cs->sc_ileave;	/* DEV_BSIZE gran */
		cbn = cbn / cs->sc_ileave;	/* DEV_BSIZE * ileave gran */

		/*
		 * Figure out which interleave table to use.
		 */
		for (ii = cs->sc_itable; ii->ii_ndisk; ii++) {
			if (ii->ii_startblk > cbn)
				break;
		}
		ii--;

		/*
		 * off is the logical superblock relative to the beginning 
		 * of this interleave block.  
		 */
		off = cbn - ii->ii_startblk;

		/*
		 * We must calculate which disk component to use (ccdisk),
		 * and recalculate cbn to be the superblock relative to
		 * the beginning of the component.  This is typically done by
		 * adding 'off' and ii->ii_startoff together.  However, 'off'
		 * must typically be divided by the number of components in
		 * this interleave array to be properly convert it from a
		 * CCD-relative logical superblock number to a 
		 * component-relative superblock number.
		 */
		if (ii->ii_ndisk == 1) {
			/*
			 * When we have just one disk, it can't be a mirror
			 * or a parity config.
			 */
			ccdisk = ii->ii_index[0];
			cbn = ii->ii_startoff + off;
		} else {
			if (cs->sc_flags & CCDF_MIRROR) {
				/*
				 * We have forced a uniform mapping, resulting
				 * in a single interleave array.  We double
				 * up on the first half of the available
				 * components and our mirror is in the second
				 * half.  This only works with a single 
				 * interleave array because doubling up
				 * doubles the number of sectors, so there
				 * cannot be another interleave array because
				 * the next interleave array's calculations
				 * would be off.
				 */
				int ndisk2 = ii->ii_ndisk / 2;
				ccdisk = ii->ii_index[off % ndisk2];
				cbn = ii->ii_startoff + off / ndisk2;
				ci2 = &cs->sc_cinfo[ccdisk + ndisk2];
			} else {
				ccdisk = ii->ii_index[off % ii->ii_ndisk];
				cbn = ii->ii_startoff + off / ii->ii_ndisk;
			}
		}

		ci = &cs->sc_cinfo[ccdisk];

		/*
		 * Convert cbn from a superblock to a normal block so it
		 * can be used to calculate (along with cboff) the normal
		 * block index into this particular disk.
		 */
		cbn *= cs->sc_ileave;
	}

	/*
	 * Fill in the component buf structure.
	 */
	cbp = g_clone_bio(bp);
	if (cbp == NULL)
		return (ENOMEM);
	cbp->bio_done = g_std_done;
	cbp->bio_offset = dbtob(cbn + cboff + cs->sc_offset);
	cbp->bio_data = addr;
	if (cs->sc_ileave == 0)
              cbc = dbtob((off_t)(ci->ci_size - cbn));
	else
              cbc = dbtob((off_t)(cs->sc_ileave - cboff));
	cbp->bio_length = (cbc < bcount) ? cbc : bcount;

	cbp->bio_from = ci->ci_consumer;
	cb[0] = cbp;

	if (cs->sc_flags & CCDF_MIRROR) {
		cbp = g_clone_bio(bp);
		if (cbp == NULL)
			return (ENOMEM);
		cbp->bio_done = cb[0]->bio_done = ccdiodone;
		cbp->bio_offset = cb[0]->bio_offset;
		cbp->bio_data = cb[0]->bio_data;
		cbp->bio_length = cb[0]->bio_length;
		cbp->bio_from = ci2->ci_consumer;
		cbp->bio_caller1 = cb[0];
		cb[0]->bio_caller1 = cbp;
		cb[1] = cbp;
	}
	return (0);
}