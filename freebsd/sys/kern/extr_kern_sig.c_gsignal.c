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
struct pgrp {int dummy; } ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 struct pgrp* pgfind (int) ; 
 int /*<<< orphan*/  pgsignal (struct pgrp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

void
gsignal(int pgid, int sig, ksiginfo_t *ksi)
{
	struct pgrp *pgrp;

	if (pgid != 0) {
		sx_slock(&proctree_lock);
		pgrp = pgfind(pgid);
		sx_sunlock(&proctree_lock);
		if (pgrp != NULL) {
			pgsignal(pgrp, sig, 0, ksi);
			PGRP_UNLOCK(pgrp);
		}
	}
}