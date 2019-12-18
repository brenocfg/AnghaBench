#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct thread_map {int /*<<< orphan*/  thr_state; int /*<<< orphan*/  thr_lwpp; int /*<<< orphan*/  thr_tid; } ;
struct thread_info {TYPE_1__* private; } ;
typedef  scalar_t__ ptid_t ;
typedef  int /*<<< orphan*/  mapp ;
typedef  enum thread_change { ____Placeholder_thread_change } thread_change ;
typedef  int /*<<< orphan*/  change ;
struct TYPE_12__ {int lwp_id; } ;
typedef  TYPE_3__ __lwp_desc_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* to_xfer_memory ) (scalar_t__,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ;} ;
struct TYPE_13__ {TYPE_2__* private; } ;
struct TYPE_11__ {int stable; int lwpid; scalar_t__ mapp; } ;
struct TYPE_10__ {int /*<<< orphan*/  lwpid; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  DBG2 (char*) ; 
 scalar_t__ DECR_PC_AFTER_BREAK ; 
 scalar_t__ MKTID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (scalar_t__) ; 
 scalar_t__ SP_ARG0 ; 
 int /*<<< orphan*/  SP_REGNUM ; 
 int /*<<< orphan*/  add_thread_uw (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 TYPE_5__ base_ops ; 
 int /*<<< orphan*/  dbgchange (int) ; 
 int /*<<< orphan*/  dbgpid (scalar_t__) ; 
 char* dbgstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_thread (scalar_t__) ; 
 scalar_t__ find_main () ; 
 struct thread_info* find_thread_lwp (int) ; 
 TYPE_4__* find_thread_pid (scalar_t__) ; 
 scalar_t__ inferior_ptid ; 
 scalar_t__ null_ptid ; 
 scalar_t__ pid ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_lwp (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  read_map (scalar_t__,struct thread_map*) ; 
 scalar_t__ read_pc_pid (scalar_t__) ; 
 scalar_t__ read_register_pid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_4__* switchto_thread ; 
 int /*<<< orphan*/  target_pid_to_str (scalar_t__) ; 
#define  tc_cancel_complete 136 
#define  tc_invalid 135 
#define  tc_switch_begin 134 
#define  tc_switch_complete 133 
#define  tc_thread_continue 132 
#define  tc_thread_create 131 
#define  tc_thread_exit 130 
#define  tc_thread_suspend 129 
#define  tc_thread_suspend_pending 128 
 scalar_t__ thr_brk_addr ; 

__attribute__((used)) static void
libthread_stub (ptid_t ptid)
{
  CORE_ADDR sp, mapp, mapp_main;
  enum thread_change change;
  struct thread_map map;
  __lwp_desc_t lwp;
  int lwpid;
  ptid_t tid = null_ptid;
  struct thread_info *info;

  /* Check for stub breakpoint. */
  if (read_pc_pid (ptid) - DECR_PC_AFTER_BREAK != thr_brk_addr)
    return;

  /* Retrieve stub args. */
  sp = read_register_pid (SP_REGNUM, ptid);
  if (!base_ops.to_xfer_memory (sp + SP_ARG0, (char *)&mapp,
				sizeof (mapp), 0, NULL, &base_ops))
    goto err;
  if (!base_ops.to_xfer_memory (sp + SP_ARG0 + sizeof (mapp), (char *)&change,
				sizeof (change), 0, NULL, &base_ops))
    goto err;

  /* create_inferior() may not have finished yet, so notice the main
     thread to ensure that it's displayed first by add_thread(). */
  mapp_main = find_main ();

  /* Notice thread creation, deletion, or stability change. */
  switch (change) {
  case tc_switch_begin:
    if (!mapp)				/* usually means main thread */
      mapp = mapp_main;
    /* fall through */

  case tc_thread_create:
  case tc_thread_exit:
    if (!mapp)
      break;
    if (!read_map (mapp, &map))
      goto err;
    tid = MKTID (PIDGET (ptid), map.thr_tid);

    switch (change) {
    case tc_thread_create:		/* new thread */
      if (!map.thr_lwpp)
	lwpid = 0;
      else if (!read_lwp ((CORE_ADDR)map.thr_lwpp, &lwp))
	goto err;
      else
	lwpid = lwp.lwp_id;
      add_thread_uw (map.thr_tid, lwpid, mapp, tid);
      break;

    case tc_thread_exit:		/* thread has exited */
      printf_unfiltered ("[Exited %s]\n", target_pid_to_str (tid));
      delete_thread (tid);
      if (ptid_equal (tid, inferior_ptid))
	inferior_ptid = ptid;
      break;

    case tc_switch_begin:		/* lwp is switching threads */
      if (switchto_thread)
	goto err;
      if (!(switchto_thread = find_thread_pid (tid)))
	goto err;
      switchto_thread->private->stable = 0;
      break;

    default:
      break;
    }
    break;

  case tc_switch_complete:		/* lwp has switched threads */
  case tc_cancel_complete:		/* lwp didn't switch threads */
    if (!switchto_thread)
      goto err;

    if (change == tc_switch_complete)
      {
	/* If switchto_thread is the main thread, then (a) the corresponding
	   tc_switch_begin probably received a null map argument and therefore
	   (b) it may have been a spurious switch following a tc_thread_exit.

	   Therefore, explicitly query the thread's lwp before caching it in
	   its thread list entry. */

	if (!read_map (switchto_thread->private->mapp, &map))
	  goto err;
	if (map.thr_lwpp)
	  {
	    if (!read_lwp ((CORE_ADDR)map.thr_lwpp, &lwp))
	      goto err;
	    if ((info = find_thread_lwp (lwp.lwp_id)))
	      info->private->lwpid = 0;
	    switchto_thread->private->lwpid = lwp.lwp_id;
	  }
      }

    switchto_thread->private->stable = 1;
    switchto_thread = NULL;
    break;

  case tc_invalid:
  case tc_thread_suspend:
  case tc_thread_suspend_pending:
  case tc_thread_continue:
  err:
    DBG(("unexpected condition in libthread_stub()"));
    break;
  }

  DBG2(("libthread_stub(%s): %s %s %s", dbgpid (pid), dbgpid (tid),
	dbgchange (change), tid ? dbgstate (map.thr_state) : ""));
}