#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ps_prochandle {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int gdb_ps_addr_t ;
struct TYPE_5__ {int (* to_xfer_memory ) (int,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int (* to_xfer_memory ) (int,char*,int,int,int /*<<< orphan*/ ,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PS_ERR ; 
 int /*<<< orphan*/  PS_OK ; 
 int bfd_get_arch_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_ops ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 TYPE_3__ orig_core_ops ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_first_available () ; 
 TYPE_1__ procfs_ops ; 
 struct cleanup* save_inferior_ptid () ; 
 int stub1 (int,char*,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int stub2 (int,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_thread_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,long) ; 

__attribute__((used)) static ps_err_e
rw_common (int dowrite, const struct ps_prochandle *ph, gdb_ps_addr_t addr,
	   char *buf, int size)
{
  struct cleanup *old_chain;

  old_chain = save_inferior_ptid ();

  if (is_thread (inferior_ptid) ||	/* A thread */
      !target_thread_alive (inferior_ptid))	/* An lwp, but not alive */
    inferior_ptid = procfs_first_available ();	/* Find any live lwp.  */
  /* Note: don't need to call switch_to_thread; we're just reading memory.  */

#if defined (__sparcv9)
  /* For Sparc64 cross Sparc32, make sure the address has not been
     accidentally sign-extended (or whatever) to beyond 32 bits.  */
  if (bfd_get_arch_size (exec_bfd) == 32)
    addr &= 0xffffffff;
#endif

  while (size > 0)
    {
      int cc;

      /* FIXME: passing 0 as attrib argument.  */
      if (target_has_execution)
	cc = procfs_ops.to_xfer_memory (addr, buf, size,
					dowrite, 0, &procfs_ops);
      else
	cc = orig_core_ops.to_xfer_memory (addr, buf, size,
					   dowrite, 0, &core_ops);

      if (cc < 0)
	{
	  if (dowrite == 0)
	    print_sys_errmsg ("rw_common (): read", errno);
	  else
	    print_sys_errmsg ("rw_common (): write", errno);

	  do_cleanups (old_chain);

	  return PS_ERR;
	}
      else if (cc == 0)
	{
	  if (dowrite == 0)
	    warning ("rw_common (): unable to read at addr 0x%lx",
		     (long) addr);
	  else
	    warning ("rw_common (): unable to write at addr 0x%lx",
		     (long) addr);

	  do_cleanups (old_chain);

	  return PS_ERR;
	}

      size -= cc;
      buf += cc;
    }

  do_cleanups (old_chain);

  return PS_OK;
}