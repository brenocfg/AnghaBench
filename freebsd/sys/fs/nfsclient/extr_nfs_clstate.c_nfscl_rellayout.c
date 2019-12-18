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
struct nfscllayout {int /*<<< orphan*/  nfsly_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nfscl_rellayout(struct nfscllayout *lyp, int exclocked)
{

	NFSLOCKCLSTATE();
	if (exclocked != 0)
		nfsv4_unlock(&lyp->nfsly_lock, 0);
	else
		nfsv4_relref(&lyp->nfsly_lock);
	NFSUNLOCKCLSTATE();
}