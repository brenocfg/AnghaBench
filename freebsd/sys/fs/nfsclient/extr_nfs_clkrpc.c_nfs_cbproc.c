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
typedef  int /*<<< orphan*/  u_int32_t ;
struct thread {int dummy; } ;
struct nfsrv_descript {scalar_t__ nd_repstat; int /*<<< orphan*/  nd_flag; int /*<<< orphan*/ * nd_nam2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_STREAMSOCK ; 
 scalar_t__ NFSERR_DONTREPLY ; 
 int RC_DROPIT ; 
 int RC_REPLY ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  nfscl_docb (struct nfsrv_descript*,struct thread*) ; 

__attribute__((used)) static int
nfs_cbproc(struct nfsrv_descript *nd, u_int32_t xid)
{
	struct thread *td = curthread;
	int cacherep;

	if (nd->nd_nam2 == NULL)
		nd->nd_flag |= ND_STREAMSOCK;

	nfscl_docb(nd, td);
	if (nd->nd_repstat == NFSERR_DONTREPLY)
		cacherep = RC_DROPIT;
	else
		cacherep = RC_REPLY;
	return (cacherep);
}