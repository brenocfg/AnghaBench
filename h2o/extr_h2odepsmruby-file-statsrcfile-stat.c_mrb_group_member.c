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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  GETGROUPS_T ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static int
mrb_group_member(mrb_state *mrb, GETGROUPS_T gid)
{
#if defined(_WIN32) || !defined(HAVE_GETGROUPS)
  return FALSE;
#else
  int rv = FALSE;
  int groups = 16;
  GETGROUPS_T *gary = NULL;
  int anum = -1;

  if (getgid() == gid || getegid() == gid)
    return TRUE;

  /*
   * On Mac OS X (Mountain Lion), NGROUPS is 16. But libc and kernel
   * accept more larger value.
   * So we don't trunk NGROUPS anymore.
   */
  while (groups <= MRB_MAX_GROUPS) {
    gary = (GETGROUPS_T*)mrb_malloc(mrb, sizeof(GETGROUPS_T) * (unsigned int)groups);
    anum = getgroups(groups, gary);
    if (anum != -1 && anum != groups)
      break;
    groups *= 2;
    if (gary) {
      mrb_free(mrb, gary);
      gary = 0;
    }
  }
  if (anum == -1)
    return FALSE;

  while (--anum >= 0) {
    if (gary[anum] == gid) {
      rv = TRUE;
      break;
    }
  }

  if (gary) {
    mrb_free(mrb, gary);
  }
  return rv;
#endif
}