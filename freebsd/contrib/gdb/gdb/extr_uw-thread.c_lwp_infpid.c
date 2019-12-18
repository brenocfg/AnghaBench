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
 int /*<<< orphan*/  infpid_cleanup ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_ptid ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_infpid ; 
 int /*<<< orphan*/  thr_to_lwp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lwp_infpid (void)
{
  ptid_t ptid = thr_to_lwp (inferior_ptid);
  DBG2((" inferior_ptid to procfs: %s => %s",
	dbgpid (inferior_ptid), dbgpid (ptid)));

  if (ptid_equal (ptid, null_ptid))
    return 0;

  inferior_ptid = ptid;
  infpid_cleanup = make_cleanup (thr_infpid, NULL);
  return 1;
}