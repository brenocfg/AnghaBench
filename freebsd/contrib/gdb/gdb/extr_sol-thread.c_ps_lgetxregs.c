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
typedef  scalar_t__ ps_err_e ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIOCGXREG ; 
 scalar_t__ PS_ERR ; 
 scalar_t__ PS_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ get_lwp_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_sys_errmsg (char*,int /*<<< orphan*/ ) ; 

ps_err_e
ps_lgetxregs (gdb_ps_prochandle_t ph, lwpid_t lwpid, caddr_t xregset)
{
#if 0
  int lwp_fd;
  ps_err_e val;

  val = get_lwp_fd (ph, lwpid, &lwp_fd);
  if (val != PS_OK)
    return val;

  if (ioctl (lwp_fd, PIOCGXREG, xregset))
    {
      print_sys_errmsg ("ps_lgetxregs (): PIOCGXREG", errno);
      return PS_ERR;
    }
#endif

  return PS_OK;
}