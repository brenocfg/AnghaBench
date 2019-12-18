#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_6__ {int lwp_id; } ;
struct TYPE_5__ {int thr_tid; int /*<<< orphan*/  thr_lwpp; } ;
struct TYPE_7__ {int /*<<< orphan*/  mapp; TYPE_2__ lwp; TYPE_1__ map; } ;
typedef  TYPE_3__ iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  MKTID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_thread_uw (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_thread_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 

__attribute__((used)) static int
notice_thread (iter_t *iter, void *data)
{
  int thrid = iter->map.thr_tid;
  int lwpid = !iter->map.thr_lwpp ? 0 : iter->lwp.lwp_id;
  ptid_t ptid = MKTID (PIDGET (inferior_ptid), thrid);

  if (!find_thread_pid (ptid) && (!data || thrid == 1))
    add_thread_uw (thrid, lwpid, iter->mapp, ptid);

  return 0;
}