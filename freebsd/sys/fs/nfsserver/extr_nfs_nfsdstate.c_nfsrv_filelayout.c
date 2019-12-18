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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  qval; } ;
struct nfsrv_descript {TYPE_2__ nd_clientid; } ;
struct TYPE_3__ {int /*<<< orphan*/  qval; } ;
struct nfslayout {scalar_t__ lay_layoutlen; scalar_t__ lay_xdr; int /*<<< orphan*/  lay_fsid; TYPE_1__ lay_clientid; int /*<<< orphan*/  lay_fh; int /*<<< orphan*/  lay_flags; int /*<<< orphan*/  lay_type; } ;
typedef  int /*<<< orphan*/  fsid_t ;
typedef  char fhandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NFSBCOPY (char*,int /*<<< orphan*/ *,int) ; 
 int NFSFLAYUTIL_STRIPE_MASK ; 
 int NFSLAYOUTIOMODE_RW ; 
 int /*<<< orphan*/  NFSLAYOUT_NFSV4_1_FILES ; 
 int /*<<< orphan*/  NFSLAY_READ ; 
 int /*<<< orphan*/  NFSLAY_RW ; 
 int NFSX_UNSIGNED ; 
 int NFSX_V4DEVICEID ; 
 scalar_t__ NFSX_V4FILELAYOUT ; 
 int NFSX_V4PNFSFH ; 
 struct nfslayout* malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txdr_hyper (scalar_t__,int /*<<< orphan*/ *) ; 
 void* txdr_unsigned (int) ; 

__attribute__((used)) static struct nfslayout *
nfsrv_filelayout(struct nfsrv_descript *nd, int iomode, fhandle_t *fhp,
    fhandle_t *dsfhp, char *devid, fsid_t fs)
{
	uint32_t *tl;
	struct nfslayout *lyp;
	uint64_t pattern_offset;

	lyp = malloc(sizeof(struct nfslayout) + NFSX_V4FILELAYOUT, M_NFSDSTATE,
	    M_WAITOK | M_ZERO);
	lyp->lay_type = NFSLAYOUT_NFSV4_1_FILES;
	if (iomode == NFSLAYOUTIOMODE_RW)
		lyp->lay_flags = NFSLAY_RW;
	else
		lyp->lay_flags = NFSLAY_READ;
	NFSBCOPY(fhp, &lyp->lay_fh, sizeof(*fhp));
	lyp->lay_clientid.qval = nd->nd_clientid.qval;
	lyp->lay_fsid = fs;

	/* Fill in the xdr for the files layout. */
	tl = (uint32_t *)lyp->lay_xdr;
	NFSBCOPY(devid, tl, NFSX_V4DEVICEID);		/* Device ID. */
	tl += (NFSX_V4DEVICEID / NFSX_UNSIGNED);

	/*
	 * Make the stripe size as many 64K blocks as will fit in the stripe
	 * mask. Since there is only one stripe, the stripe size doesn't really
	 * matter, except that the Linux client will only handle an exact
	 * multiple of their PAGE_SIZE (usually 4K).  I chose 64K as a value
	 * that should cover most/all arches w.r.t. PAGE_SIZE.
	 */
	*tl++ = txdr_unsigned(NFSFLAYUTIL_STRIPE_MASK & ~0xffff);
	*tl++ = 0;					/* 1st stripe index. */
	pattern_offset = 0;
	txdr_hyper(pattern_offset, tl); tl += 2;	/* Pattern offset. */
	*tl++ = txdr_unsigned(1);			/* 1 file handle. */
	*tl++ = txdr_unsigned(NFSX_V4PNFSFH);
	NFSBCOPY(dsfhp, tl, sizeof(*dsfhp));
	lyp->lay_layoutlen = NFSX_V4FILELAYOUT;
	return (lyp);
}