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
struct ptrace_lwpinfo {scalar_t__ pl_lwpid; } ;
typedef  int /*<<< orphan*/  pl ;
typedef  long lwpid_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_LWPINFO ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  core_bfd ; 
 int /*<<< orphan*/  fbsd_core_get_first_lwp ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_has_execution ; 

__attribute__((used)) static long
get_current_lwp (int pid)
{
  struct ptrace_lwpinfo pl;
  lwpid_t lwpid;

  if (!target_has_execution)
    {
      lwpid = 0;
      bfd_map_over_sections (core_bfd, fbsd_core_get_first_lwp, &lwpid);
      return lwpid;
    }
  if (ptrace (PT_LWPINFO, pid, (caddr_t)&pl, sizeof(pl)))
    perror_with_name("PT_LWPINFO");

  return (long)pl.pl_lwpid;
}