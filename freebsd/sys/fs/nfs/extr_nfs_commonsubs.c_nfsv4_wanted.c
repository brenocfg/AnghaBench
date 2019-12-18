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
struct nfsv4lock {int nfslock_lock; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int NFSV4LOCK_WANTED ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsv4_wanted(struct nfsv4lock *lp)
{

	if (lp->nfslock_lock & NFSV4LOCK_WANTED) {
		lp->nfslock_lock &= ~NFSV4LOCK_WANTED;
		wakeup((caddr_t)&lp->nfslock_lock);
	}
}