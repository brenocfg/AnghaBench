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
typedef  scalar_t__ u_int32_t ;
struct nfsrv_descript {int nd_repstat; size_t nd_procnum; } ;

/* Variables and functions */
 int EBADRPC ; 
 short NFSERR_BADIOMODE ; 
 short NFSERR_BADXDR ; 
 int NFSERR_MINORVERMISMATCH ; 
 int NFSERR_OPILLEGAL ; 
 size_t NFSPROC_NOOP ; 
 size_t NFSV4OP_CBNOPS ; 
 scalar_t__ NFSV4_MINORVERSION ; 
 short** nfscl_cberrmap ; 
 int txdr_unsigned (short) ; 

__attribute__((used)) static int
nfscl_errmap(struct nfsrv_descript *nd, u_int32_t minorvers)
{
	short *defaulterrp, *errp;

	if (!nd->nd_repstat)
		return (0);
	if (nd->nd_procnum == NFSPROC_NOOP)
		return (txdr_unsigned(nd->nd_repstat & 0xffff));
	if (nd->nd_repstat == EBADRPC)
		return (txdr_unsigned(NFSERR_BADXDR));
	if (nd->nd_repstat == NFSERR_MINORVERMISMATCH ||
	    nd->nd_repstat == NFSERR_OPILLEGAL)
		return (txdr_unsigned(nd->nd_repstat));
	if (nd->nd_repstat >= NFSERR_BADIOMODE && nd->nd_repstat < 20000 &&
	    minorvers > NFSV4_MINORVERSION) {
		/* NFSv4.n error. */
		return (txdr_unsigned(nd->nd_repstat));
	}
	if (nd->nd_procnum < NFSV4OP_CBNOPS)
		errp = defaulterrp = nfscl_cberrmap[nd->nd_procnum];
	else
		return (txdr_unsigned(nd->nd_repstat));
	while (*++errp)
		if (*errp == (short)nd->nd_repstat)
			return (txdr_unsigned(nd->nd_repstat));
	return (txdr_unsigned(*defaulterrp));
}