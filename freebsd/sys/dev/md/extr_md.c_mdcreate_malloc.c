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
struct md_s {scalar_t__ fwsectors; scalar_t__ fwheads; int flags; int mediasize; int sectorsize; int /*<<< orphan*/  indir; int /*<<< orphan*/  uma; int /*<<< orphan*/  name; } ;
struct md_req {int md_options; scalar_t__ md_sectorsize; scalar_t__ md_fwsectors; scalar_t__ md_fwheads; } ;
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MD_AUTOUNIT ; 
 int MD_COMPRESS ; 
 int MD_FORCE ; 
 int MD_RESERVE ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  dimension (int) ; 
 scalar_t__ md_malloc_wait ; 
 int /*<<< orphan*/  powerof2 (scalar_t__) ; 
 int s_write (int /*<<< orphan*/ ,int,uintptr_t) ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zcreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mdcreate_malloc(struct md_s *sc, struct md_req *mdr)
{
	uintptr_t sp;
	int error;
	off_t u;

	error = 0;
	if (mdr->md_options & ~(MD_AUTOUNIT | MD_COMPRESS | MD_RESERVE))
		return (EINVAL);
	if (mdr->md_sectorsize != 0 && !powerof2(mdr->md_sectorsize))
		return (EINVAL);
	/* Compression doesn't make sense if we have reserved space */
	if (mdr->md_options & MD_RESERVE)
		mdr->md_options &= ~MD_COMPRESS;
	if (mdr->md_fwsectors != 0)
		sc->fwsectors = mdr->md_fwsectors;
	if (mdr->md_fwheads != 0)
		sc->fwheads = mdr->md_fwheads;
	sc->flags = mdr->md_options & (MD_COMPRESS | MD_FORCE);
	sc->indir = dimension(sc->mediasize / sc->sectorsize);
	sc->uma = uma_zcreate(sc->name, sc->sectorsize, NULL, NULL, NULL, NULL,
	    0x1ff, 0);
	if (mdr->md_options & MD_RESERVE) {
		off_t nsectors;

		nsectors = sc->mediasize / sc->sectorsize;
		for (u = 0; u < nsectors; u++) {
			sp = (uintptr_t)uma_zalloc(sc->uma, (md_malloc_wait ?
			    M_WAITOK : M_NOWAIT) | M_ZERO);
			if (sp != 0)
				error = s_write(sc->indir, u, sp);
			else
				error = ENOMEM;
			if (error != 0)
				break;
		}
	}
	return (error);
}