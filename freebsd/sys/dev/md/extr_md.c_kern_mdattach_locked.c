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
struct thread {int dummy; } ;
struct md_s {int unit; unsigned int mediasize; unsigned int sectorsize; int type; int /*<<< orphan*/  start; int /*<<< orphan*/  label; } ;
struct md_req {unsigned int md_sectorsize; unsigned int md_mediasize; int md_options; int md_unit; int /*<<< orphan*/ * md_label; int /*<<< orphan*/  md_type; } ;

/* Variables and functions */
 unsigned int DEV_BSIZE ; 
 int EDOOFUS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int INT_MAX ; 
 unsigned int MAXPHYS ; 
 int MD_AUTOUNIT ; 
#define  MD_MALLOC 132 
#define  MD_NULL 131 
#define  MD_PRELOAD 130 
#define  MD_SWAP 129 
#define  MD_VNODE 128 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int copyinstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_sx ; 
 int mdcreate_malloc (struct md_s*,struct md_req*) ; 
 int mdcreate_null (struct md_s*,struct md_req*,struct thread*) ; 
 int mdcreate_swap (struct md_s*,struct md_req*,struct thread*) ; 
 int mdcreate_vnode (struct md_s*,struct md_req*,struct thread*) ; 
 int /*<<< orphan*/  mddestroy (struct md_s*,struct thread*) ; 
 int /*<<< orphan*/  mdinit (struct md_s*) ; 
 struct md_s* mdnew (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdstart_malloc ; 
 int /*<<< orphan*/  mdstart_null ; 
 int /*<<< orphan*/  mdstart_swap ; 
 int /*<<< orphan*/  mdstart_vnode ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_mdattach_locked(struct thread *td, struct md_req *mdr)
{
	struct md_s *sc;
	unsigned sectsize;
	int error, i;

	sx_assert(&md_sx, SA_XLOCKED);

	switch (mdr->md_type) {
	case MD_MALLOC:
	case MD_PRELOAD:
	case MD_VNODE:
	case MD_SWAP:
	case MD_NULL:
		break;
	default:
		return (EINVAL);
	}
	if (mdr->md_sectorsize == 0)
		sectsize = DEV_BSIZE;
	else
		sectsize = mdr->md_sectorsize;
	if (sectsize > MAXPHYS || mdr->md_mediasize < sectsize)
		return (EINVAL);
	if (mdr->md_options & MD_AUTOUNIT)
		sc = mdnew(-1, &error, mdr->md_type);
	else {
		if (mdr->md_unit > INT_MAX)
			return (EINVAL);
		sc = mdnew(mdr->md_unit, &error, mdr->md_type);
	}
	if (sc == NULL)
		return (error);
	if (mdr->md_label != NULL)
		error = copyinstr(mdr->md_label, sc->label,
		    sizeof(sc->label), NULL);
	if (error != 0)
		goto err_after_new;
	if (mdr->md_options & MD_AUTOUNIT)
		mdr->md_unit = sc->unit;
	sc->mediasize = mdr->md_mediasize;
	sc->sectorsize = sectsize;
	error = EDOOFUS;
	switch (sc->type) {
	case MD_MALLOC:
		sc->start = mdstart_malloc;
		error = mdcreate_malloc(sc, mdr);
		break;
	case MD_PRELOAD:
		/*
		 * We disallow attaching preloaded memory disks via
		 * ioctl. Preloaded memory disks are automatically
		 * attached in g_md_init().
		 */
		error = EOPNOTSUPP;
		break;
	case MD_VNODE:
		sc->start = mdstart_vnode;
		error = mdcreate_vnode(sc, mdr, td);
		break;
	case MD_SWAP:
		sc->start = mdstart_swap;
		error = mdcreate_swap(sc, mdr, td);
		break;
	case MD_NULL:
		sc->start = mdstart_null;
		error = mdcreate_null(sc, mdr, td);
		break;
	}
err_after_new:
	if (error != 0) {
		mddestroy(sc, td);
		return (error);
	}

	/* Prune off any residual fractional sector */
	i = sc->mediasize % sc->sectorsize;
	sc->mediasize -= i;

	mdinit(sc);
	return (0);
}