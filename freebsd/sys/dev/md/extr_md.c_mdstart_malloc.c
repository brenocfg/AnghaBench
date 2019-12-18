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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  uintptr_t u_char ;
struct md_s {uintptr_t sectorsize; int flags; int /*<<< orphan*/  uma; int /*<<< orphan*/  indir; } ;
struct bio {int bio_cmd; int bio_flags; uintptr_t* bio_data; int bio_ma_offset; uintptr_t bio_length; uintptr_t bio_offset; scalar_t__ bio_resid; int /*<<< orphan*/ * bio_ma; } ;
typedef  uintptr_t off_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
#define  BIO_DELETE 130 
#define  BIO_READ 129 
 int BIO_UNMAPPED ; 
 int BIO_VLIST ; 
#define  BIO_WRITE 128 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MD_COMPRESS ; 
 int /*<<< orphan*/  MD_MALLOC_MOVE_CMP ; 
 int /*<<< orphan*/  MD_MALLOC_MOVE_FILL ; 
 int /*<<< orphan*/  MD_MALLOC_MOVE_READ ; 
 int /*<<< orphan*/  MD_MALLOC_MOVE_WRITE ; 
 int /*<<< orphan*/  MD_MALLOC_MOVE_ZERO ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (uintptr_t*,void*,uintptr_t) ; 
 int /*<<< orphan*/  bzero (uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/  cpu_flush_dcache (uintptr_t*,uintptr_t) ; 
 int md_malloc_move_ma (int /*<<< orphan*/ **,int*,uintptr_t,void*,uintptr_t,int /*<<< orphan*/ ) ; 
 int md_malloc_move_vlist (int /*<<< orphan*/ **,int*,uintptr_t,void*,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ md_malloc_wait ; 
 int /*<<< orphan*/  memset (uintptr_t*,uintptr_t,uintptr_t) ; 
 uintptr_t s_read (int /*<<< orphan*/ ,uintptr_t) ; 
 int s_write (int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
mdstart_malloc(struct md_s *sc, struct bio *bp)
{
	u_char *dst;
	vm_page_t *m;
	bus_dma_segment_t *vlist;
	int i, error, error1, ma_offs, notmapped;
	off_t secno, nsec, uc;
	uintptr_t sp, osp;

	switch (bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
		break;
	default:
		return (EOPNOTSUPP);
	}

	notmapped = (bp->bio_flags & BIO_UNMAPPED) != 0;
	vlist = (bp->bio_flags & BIO_VLIST) != 0 ?
	    (bus_dma_segment_t *)bp->bio_data : NULL;
	if (notmapped) {
		m = bp->bio_ma;
		ma_offs = bp->bio_ma_offset;
		dst = NULL;
		KASSERT(vlist == NULL, ("vlists cannot be unmapped"));
	} else if (vlist != NULL) {
		ma_offs = bp->bio_ma_offset;
		dst = NULL;
	} else {
		dst = bp->bio_data;
	}

	nsec = bp->bio_length / sc->sectorsize;
	secno = bp->bio_offset / sc->sectorsize;
	error = 0;
	while (nsec--) {
		osp = s_read(sc->indir, secno);
		if (bp->bio_cmd == BIO_DELETE) {
			if (osp != 0)
				error = s_write(sc->indir, secno, 0);
		} else if (bp->bio_cmd == BIO_READ) {
			if (osp == 0) {
				if (notmapped) {
					error = md_malloc_move_ma(&m, &ma_offs,
					    sc->sectorsize, NULL, 0,
					    MD_MALLOC_MOVE_ZERO);
				} else if (vlist != NULL) {
					error = md_malloc_move_vlist(&vlist,
					    &ma_offs, sc->sectorsize, NULL, 0,
					    MD_MALLOC_MOVE_ZERO);
				} else
					bzero(dst, sc->sectorsize);
			} else if (osp <= 255) {
				if (notmapped) {
					error = md_malloc_move_ma(&m, &ma_offs,
					    sc->sectorsize, NULL, osp,
					    MD_MALLOC_MOVE_FILL);
				} else if (vlist != NULL) {
					error = md_malloc_move_vlist(&vlist,
					    &ma_offs, sc->sectorsize, NULL, osp,
					    MD_MALLOC_MOVE_FILL);
				} else
					memset(dst, osp, sc->sectorsize);
			} else {
				if (notmapped) {
					error = md_malloc_move_ma(&m, &ma_offs,
					    sc->sectorsize, (void *)osp, 0,
					    MD_MALLOC_MOVE_READ);
				} else if (vlist != NULL) {
					error = md_malloc_move_vlist(&vlist,
					    &ma_offs, sc->sectorsize,
					    (void *)osp, 0,
					    MD_MALLOC_MOVE_READ);
				} else {
					bcopy((void *)osp, dst, sc->sectorsize);
					cpu_flush_dcache(dst, sc->sectorsize);
				}
			}
			osp = 0;
		} else if (bp->bio_cmd == BIO_WRITE) {
			if (sc->flags & MD_COMPRESS) {
				if (notmapped) {
					error1 = md_malloc_move_ma(&m, &ma_offs,
					    sc->sectorsize, &uc, 0,
					    MD_MALLOC_MOVE_CMP);
					i = error1 == 0 ? sc->sectorsize : 0;
				} else if (vlist != NULL) {
					error1 = md_malloc_move_vlist(&vlist,
					    &ma_offs, sc->sectorsize, &uc, 0,
					    MD_MALLOC_MOVE_CMP);
					i = error1 == 0 ? sc->sectorsize : 0;
				} else {
					uc = dst[0];
					for (i = 1; i < sc->sectorsize; i++) {
						if (dst[i] != uc)
							break;
					}
				}
			} else {
				i = 0;
				uc = 0;
			}
			if (i == sc->sectorsize) {
				if (osp != uc)
					error = s_write(sc->indir, secno, uc);
			} else {
				if (osp <= 255) {
					sp = (uintptr_t)uma_zalloc(sc->uma,
					    md_malloc_wait ? M_WAITOK :
					    M_NOWAIT);
					if (sp == 0) {
						error = ENOSPC;
						break;
					}
					if (notmapped) {
						error = md_malloc_move_ma(&m,
						    &ma_offs, sc->sectorsize,
						    (void *)sp, 0,
						    MD_MALLOC_MOVE_WRITE);
					} else if (vlist != NULL) {
						error = md_malloc_move_vlist(
						    &vlist, &ma_offs,
						    sc->sectorsize, (void *)sp,
						    0, MD_MALLOC_MOVE_WRITE);
					} else {
						bcopy(dst, (void *)sp,
						    sc->sectorsize);
					}
					error = s_write(sc->indir, secno, sp);
				} else {
					if (notmapped) {
						error = md_malloc_move_ma(&m,
						    &ma_offs, sc->sectorsize,
						    (void *)osp, 0,
						    MD_MALLOC_MOVE_WRITE);
					} else if (vlist != NULL) {
						error = md_malloc_move_vlist(
						    &vlist, &ma_offs,
						    sc->sectorsize, (void *)osp,
						    0, MD_MALLOC_MOVE_WRITE);
					} else {
						bcopy(dst, (void *)osp,
						    sc->sectorsize);
					}
					osp = 0;
				}
			}
		} else {
			error = EOPNOTSUPP;
		}
		if (osp > 255)
			uma_zfree(sc->uma, (void*)osp);
		if (error != 0)
			break;
		secno++;
		if (!notmapped && vlist == NULL)
			dst += sc->sectorsize;
	}
	bp->bio_resid = 0;
	return (error);
}