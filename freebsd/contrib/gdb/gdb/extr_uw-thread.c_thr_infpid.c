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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG2 (char*) ; 
 int /*<<< orphan*/  dbgpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  lwp_to_thr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thr_infpid (void *unused)
{
  ptid_t ptid = lwp_to_thr (inferior_ptid);
  DBG2((" inferior_ptid from procfs: %s => %s",
	dbgpid (inferior_ptid), dbgpid (ptid)));
  inferior_ptid = ptid;
}