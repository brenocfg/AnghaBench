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
struct TYPE_5__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct vattr {scalar_t__ va_flags; scalar_t__ va_uid; scalar_t__ va_gid; scalar_t__ va_mode; int va_vaflags; scalar_t__ va_size; TYPE_2__ va_mtime; TYPE_1__ va_atime; } ;
struct puffs_usermount {int dummy; } ;
struct TYPE_6__ {int va_type; scalar_t__ va_bytes; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; } ;
struct puffs_node {TYPE_3__ pn_va; } ;
struct puffs_cred {int dummy; } ;

/* Variables and functions */
 int EISDIR ; 
 int EOPNOTSUPP ; 
 scalar_t__ PUFFS_VNOVAL ; 
 int VA_UTIMES_NULL ; 
#define  VBLK 132 
#define  VCHR 131 
#define  VDIR 130 
#define  VFIFO 129 
#define  VREG 128 
 int /*<<< orphan*/  dtfs_setsize (struct puffs_node*,scalar_t__) ; 
 int puffs_access_chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,struct puffs_cred const*) ; 
 int puffs_access_chown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct puffs_cred const*) ; 
 int puffs_access_times (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct puffs_cred const*) ; 
 int /*<<< orphan*/  puffs_setvattr (TYPE_3__*,struct vattr const*) ; 

int
dtfs_node_setattr(struct puffs_usermount *pu, void *opc,
	const struct vattr *va, const struct puffs_cred *pcr)
{
	struct puffs_node *pn = opc;
	int rv;

	/* check permissions */
	if (va->va_flags != PUFFS_VNOVAL)
		return EOPNOTSUPP;

	if (va->va_uid != PUFFS_VNOVAL || va->va_gid != PUFFS_VNOVAL) {
		rv = puffs_access_chown(pn->pn_va.va_uid, pn->pn_va.va_gid,
		    va->va_uid, va->va_gid, pcr);
		if (rv)
			return rv;
	}

	if (va->va_mode != PUFFS_VNOVAL) {
		rv = puffs_access_chmod(pn->pn_va.va_uid, pn->pn_va.va_gid,
		    pn->pn_va.va_type, va->va_mode, pcr);
		if (rv)
			return rv;
	}

	if ((va->va_atime.tv_sec != PUFFS_VNOVAL
	      && va->va_atime.tv_nsec != PUFFS_VNOVAL)
	    || (va->va_mtime.tv_sec != PUFFS_VNOVAL
	      && va->va_mtime.tv_nsec != PUFFS_VNOVAL)) {
		rv = puffs_access_times(pn->pn_va.va_uid, pn->pn_va.va_gid,
		    pn->pn_va.va_mode, va->va_vaflags & VA_UTIMES_NULL, pcr);
		if (rv)
			return rv;
	}

	if (va->va_size != PUFFS_VNOVAL) {
		switch (pn->pn_va.va_type) {
		case VREG:
			dtfs_setsize(pn, va->va_size);
			pn->pn_va.va_bytes = va->va_size;
			break;
		case VBLK:
		case VCHR:
		case VFIFO:
			break;
		case VDIR:
			return EISDIR;
		default:
			return EOPNOTSUPP;
		}
	}

	puffs_setvattr(&pn->pn_va, va);

	return 0;
}