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
typedef  int uint32_t ;
struct nfsclrecalllayout {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqid; } ;
struct nfscllayout {int nfsly_flags; TYPE_1__ nfsly_stateid; int /*<<< orphan*/  nfsly_flayrw; int /*<<< orphan*/  nfsly_flayread; } ;
struct nfsclds {int dummy; } ;
struct nfscldevinfo {int /*<<< orphan*/  nfsdi_deviceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NFSLAYRECALL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int) ; 
 int NFSLAYOUTIOMODE_READ ; 
 int NFSLAYOUTIOMODE_RW ; 
 int /*<<< orphan*/  NFSLAYOUTRETURN_FILE ; 
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int NFSLY_RECALL ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  free (struct nfsclrecalllayout*,int /*<<< orphan*/ ) ; 
 struct nfsclrecalllayout* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_cancelreqs (struct nfsclds*) ; 
 int /*<<< orphan*/  nfscl_layoutrecall (int /*<<< orphan*/ ,struct nfscllayout*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct nfsclrecalllayout*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
nfscl_dserr(uint32_t op, uint32_t stat, struct nfscldevinfo *dp,
    struct nfscllayout *lyp, struct nfsclds *dsp)
{
	struct nfsclrecalllayout *recallp;
	uint32_t iomode;

	printf("DS being disabled, error=%d\n", stat);
	/* Set up the return of the layout. */
	recallp = malloc(sizeof(*recallp), M_NFSLAYRECALL, M_WAITOK);
	iomode = 0;
	NFSLOCKCLSTATE();
	if ((lyp->nfsly_flags & NFSLY_RECALL) == 0) {
		if (!LIST_EMPTY(&lyp->nfsly_flayread))
			iomode |= NFSLAYOUTIOMODE_READ;
		if (!LIST_EMPTY(&lyp->nfsly_flayrw))
			iomode |= NFSLAYOUTIOMODE_RW;
		(void)nfscl_layoutrecall(NFSLAYOUTRETURN_FILE, lyp, iomode,
		    0, UINT64_MAX, lyp->nfsly_stateid.seqid, stat, op,
		    dp->nfsdi_deviceid, recallp);
		NFSUNLOCKCLSTATE();
		NFSCL_DEBUG(4, "nfscl_dserr recall iomode=%d\n", iomode);
	} else {
		NFSUNLOCKCLSTATE();
		free(recallp, M_NFSLAYRECALL);
	}

	/* And shut the TCP connection down. */
	nfscl_cancelreqs(dsp);
}