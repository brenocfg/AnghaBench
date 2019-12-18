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
struct ptrace_lwpinfo {int dummy; } ;
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_ERR ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  PT_LWPINFO ; 
 scalar_t__ fbsd_thread_core ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

ps_err_e
ps_linfo(struct ps_prochandle *ph, lwpid_t lwpid, void *info)
{
  if (fbsd_thread_core) {
    /* XXX should verify lwpid and make a pseudo lwp info */
    memset(info, 0, sizeof(struct ptrace_lwpinfo));
    return PS_OK;
  }

  if (ptrace (PT_LWPINFO, lwpid, info, sizeof(struct ptrace_lwpinfo)) == -1)
    return PS_ERR;
  return PS_OK;
}