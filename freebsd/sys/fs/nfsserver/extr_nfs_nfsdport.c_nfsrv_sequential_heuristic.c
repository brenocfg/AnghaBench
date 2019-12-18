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
typedef  scalar_t__ vm_offset_t ;
struct vnode {TYPE_2__* v_mount; } ;
struct uio {scalar_t__ uio_offset; int /*<<< orphan*/  uio_resid; } ;
struct nfsheur {scalar_t__ nh_use; scalar_t__ nh_nextoff; int nh_seqcount; struct vnode* nh_vp; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_iosize; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int IO_SEQMAX ; 
 int MAX_REORDERED_RPC ; 
 scalar_t__ NHUSE_INC ; 
 scalar_t__ NHUSE_INIT ; 
 scalar_t__ NHUSE_MAX ; 
 int NUM_HEURISTIC ; 
 scalar_t__ howmany (int /*<<< orphan*/ ,int) ; 
 int imax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsheur* nfsheur ; 
 int qabs (scalar_t__) ; 

__attribute__((used)) static struct nfsheur *
nfsrv_sequential_heuristic(struct uio *uio, struct vnode *vp)
{
	struct nfsheur *nh;
	int hi, try;

	/* Locate best candidate. */
	try = 32;
	hi = ((int)(vm_offset_t)vp / sizeof(struct vnode)) % NUM_HEURISTIC;
	nh = &nfsheur[hi];
	while (try--) {
		if (nfsheur[hi].nh_vp == vp) {
			nh = &nfsheur[hi];
			break;
		}
		if (nfsheur[hi].nh_use > 0)
			--nfsheur[hi].nh_use;
		hi = (hi + 1) % NUM_HEURISTIC;
		if (nfsheur[hi].nh_use < nh->nh_use)
			nh = &nfsheur[hi];
	}

	/* Initialize hint if this is a new file. */
	if (nh->nh_vp != vp) {
		nh->nh_vp = vp;
		nh->nh_nextoff = uio->uio_offset;
		nh->nh_use = NHUSE_INIT;
		if (uio->uio_offset == 0)
			nh->nh_seqcount = 4;
		else
			nh->nh_seqcount = 1;
	}

	/* Calculate heuristic. */
	if ((uio->uio_offset == 0 && nh->nh_seqcount > 0) ||
	    uio->uio_offset == nh->nh_nextoff) {
		/* See comments in vfs_vnops.c:sequential_heuristic(). */
		nh->nh_seqcount += howmany(uio->uio_resid, 16384);
		if (nh->nh_seqcount > IO_SEQMAX)
			nh->nh_seqcount = IO_SEQMAX;
	} else if (qabs(uio->uio_offset - nh->nh_nextoff) <= MAX_REORDERED_RPC *
	    imax(vp->v_mount->mnt_stat.f_iosize, uio->uio_resid)) {
		/* Probably a reordered RPC, leave seqcount alone. */
	} else if (nh->nh_seqcount > 1) {
		nh->nh_seqcount /= 2;
	} else {
		nh->nh_seqcount = 0;
	}
	nh->nh_use += NHUSE_INC;
	if (nh->nh_use > NHUSE_MAX)
		nh->nh_use = NHUSE_MAX;
	return (nh);
}