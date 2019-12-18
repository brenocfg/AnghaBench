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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RFHIGHPID ; 
 scalar_t__ __predict_false (int) ; 
 int arc4random () ; 
 int /*<<< orphan*/  bit_ffc_at (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ *,int) ; 
 int lastpid ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int pid_max ; 
 int /*<<< orphan*/  proc_id_grpidmap ; 
 int /*<<< orphan*/  proc_id_pidmap ; 
 int /*<<< orphan*/  proc_id_reapmap ; 
 int /*<<< orphan*/  proc_id_sessidmap ; 
 int /*<<< orphan*/  procid_lock ; 
 int randompid ; 

__attribute__((used)) static int
fork_findpid(int flags)
{
	pid_t result;
	int trypid, random;

	/*
	 * Avoid calling arc4random with procid_lock held.
	 */
	random = 0;
	if (__predict_false(randompid))
		random = arc4random() % randompid;

	mtx_lock(&procid_lock);

	trypid = lastpid + 1;
	if (flags & RFHIGHPID) {
		if (trypid < 10)
			trypid = 10;
	} else {
		trypid += random;
	}
retry:
	if (trypid >= pid_max)
		trypid = 2;

	bit_ffc_at(&proc_id_pidmap, trypid, pid_max, &result);
	if (result == -1) {
		KASSERT(trypid != 2, ("unexpectedly ran out of IDs"));
		trypid = 2;
		goto retry;
	}
	if (bit_test(&proc_id_grpidmap, result) ||
	    bit_test(&proc_id_sessidmap, result) ||
	    bit_test(&proc_id_reapmap, result)) {
		trypid = result + 1;
		goto retry;
	}

	/*
	 * RFHIGHPID does not mess with the lastpid counter during boot.
	 */
	if ((flags & RFHIGHPID) == 0)
		lastpid = result;

	bit_set(&proc_id_pidmap, result);
	mtx_unlock(&procid_lock);

	return (result);
}