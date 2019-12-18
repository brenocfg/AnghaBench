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
struct nfslockfile {int /*<<< orphan*/  lf_usecount; int /*<<< orphan*/  lf_locallock_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSTATEMUTEXPTR ; 
 int nfsv4_lock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsrv_locklf(struct nfslockfile *lfp)
{
	int gotlock;

	/* lf_usecount ensures *lfp won't be free'd */
	lfp->lf_usecount++;
	do {
		gotlock = nfsv4_lock(&lfp->lf_locallock_lck, 1, NULL,
		    NFSSTATEMUTEXPTR, NULL);
	} while (gotlock == 0);
	lfp->lf_usecount--;
}