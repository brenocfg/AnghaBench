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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct timespec {int dummy; } ;
struct nfsvattr {int /*<<< orphan*/  na_size; } ;
struct nfsrv_descript {int dummy; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int nfsrv_updatemdsattr (int /*<<< orphan*/ ,struct nfsvattr*,int /*<<< orphan*/ *) ; 

int
nfsrv_layoutcommit(struct nfsrv_descript *nd, vnode_t vp, int layouttype,
    int hasnewoff, uint64_t newoff, uint64_t offset, uint64_t len,
    int hasnewmtime, struct timespec *newmtimep, int reclaim,
    nfsv4stateid_t *stateidp, int maxcnt, char *layp, int *hasnewsizep,
    uint64_t *newsizep, struct ucred *cred, NFSPROC_T *p)
{
	struct nfsvattr na;
	int error;

	error = nfsrv_updatemdsattr(vp, &na, p);
	if (error == 0) {
		*hasnewsizep = 1;
		*newsizep = na.na_size;
	}
	return (error);
}