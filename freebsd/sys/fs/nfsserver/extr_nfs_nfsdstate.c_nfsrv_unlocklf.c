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
struct nfslockfile {int /*<<< orphan*/  lf_locallock_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsv4_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsrv_unlocklf(struct nfslockfile *lfp)
{

	nfsv4_unlock(&lfp->lf_locallock_lck, 0);
}