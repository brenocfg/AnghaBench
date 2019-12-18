#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nfslock_lock; } ;
struct nfsclclient {TYPE_1__ nfsc_lock; } ;

/* Variables and functions */
 int NFSV4LOCK_LOCK ; 
 int /*<<< orphan*/  nfsv4_relref (TYPE_1__*) ; 
 int /*<<< orphan*/  nfsv4_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfscl_clrelease(struct nfsclclient *clp)
{

	if (clp->nfsc_lock.nfslock_lock & NFSV4LOCK_LOCK)
		nfsv4_unlock(&clp->nfsc_lock, 0);
	else
		nfsv4_relref(&clp->nfsc_lock);
}