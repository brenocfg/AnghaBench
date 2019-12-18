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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

svn_boolean_t
svn_dirent_is_absolute(const char *dirent)
{
  if (! dirent)
    return FALSE;

  /* dirent is absolute if it starts with '/' on non-Windows platforms
     or with '//' on Windows platforms */
  if (dirent[0] == '/'
#ifdef SVN_USE_DOS_PATHS
      && dirent[1] == '/' /* Single '/' depends on current drive */
#endif
      )
    return TRUE;

  /* On Windows, dirent is also absolute when it starts with 'H:/'
     where 'H' is any letter. */
#ifdef SVN_USE_DOS_PATHS
  if (((dirent[0] >= 'A' && dirent[0] <= 'Z')) &&
      (dirent[1] == ':') && (dirent[2] == '/'))
     return TRUE;
#endif /* SVN_USE_DOS_PATHS */

  return FALSE;
}