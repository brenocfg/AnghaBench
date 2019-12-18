#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nfsclrecalllayout {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  seqid; } ;
struct nfscllayout {int nfsly_flags; TYPE_1__ nfsly_stateid; int /*<<< orphan*/  nfsly_flayrw; int /*<<< orphan*/  nfsly_flayread; } ;
struct nfsclclient {int dummy; } ;
struct TYPE_9__ {int n_flag; } ;
struct TYPE_8__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSHASPNFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLAYOUTIOMODE_READ ; 
 int /*<<< orphan*/  NFSLAYOUTIOMODE_RW ; 
 int /*<<< orphan*/  NFSLAYOUTRETURN_FILE ; 
 int NFSLY_RECALL ; 
 int NFSLY_RETONCLOSE ; 
 int NNOLAYOUT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VFSTONFS (int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 TYPE_5__* VTONFS (TYPE_2__*) ; 
 scalar_t__ nfs_numnfscbd ; 
 scalar_t__ nfscl_enablecallb ; 
 struct nfscllayout* nfscl_findlayout (struct nfsclclient*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfscl_layoutrecall (int /*<<< orphan*/ ,struct nfscllayout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsclrecalllayout*) ; 
 int /*<<< orphan*/  vnode_mount (TYPE_2__*) ; 

__attribute__((used)) static void
nfscl_retoncloselayout(vnode_t vp, struct nfsclclient *clp, uint8_t *fhp,
    int fhlen, struct nfsclrecalllayout **recallpp)
{
	struct nfscllayout *lyp;
	uint32_t iomode;

	if (vp->v_type != VREG || !NFSHASPNFS(VFSTONFS(vnode_mount(vp))) ||
	    nfscl_enablecallb == 0 || nfs_numnfscbd == 0 ||
	    (VTONFS(vp)->n_flag & NNOLAYOUT) != 0)
		return;
	lyp = nfscl_findlayout(clp, fhp, fhlen);
	if (lyp != NULL && (lyp->nfsly_flags & (NFSLY_RETONCLOSE |
	    NFSLY_RECALL)) == NFSLY_RETONCLOSE) {
		iomode = 0;
		if (!LIST_EMPTY(&lyp->nfsly_flayread))
			iomode |= NFSLAYOUTIOMODE_READ;
		if (!LIST_EMPTY(&lyp->nfsly_flayrw))
			iomode |= NFSLAYOUTIOMODE_RW;
		(void)nfscl_layoutrecall(NFSLAYOUTRETURN_FILE, lyp, iomode,
		    0, UINT64_MAX, lyp->nfsly_stateid.seqid, 0, 0, NULL,
		    *recallpp);
		NFSCL_DEBUG(4, "retoncls recall iomode=%d\n", iomode);
		*recallpp = NULL;
	}
}