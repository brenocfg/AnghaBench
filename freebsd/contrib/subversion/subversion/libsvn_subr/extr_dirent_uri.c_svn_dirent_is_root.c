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
typedef  int svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

svn_boolean_t
svn_dirent_is_root(const char *dirent, apr_size_t len)
{
#ifdef SVN_USE_DOS_PATHS
  /* On Windows and Cygwin, 'H:' or 'H:/' (where 'H' is any letter)
     are also root directories */
  if ((len == 2 || ((len == 3) && (dirent[2] == '/'))) &&
      (dirent[1] == ':') &&
      ((dirent[0] >= 'A' && dirent[0] <= 'Z') ||
       (dirent[0] >= 'a' && dirent[0] <= 'z')))
    return TRUE;

  /* On Windows and Cygwin //server/share is a root directory,
     and on Cygwin //drive is a drive alias */
  if (len >= 2 && dirent[0] == '/' && dirent[1] == '/'
      && dirent[len - 1] != '/')
    {
      int segments = 0;
      apr_size_t i;
      for (i = len; i >= 2; i--)
        {
          if (dirent[i] == '/')
            {
              segments ++;
              if (segments > 1)
                return FALSE;
            }
        }
#ifdef __CYGWIN__
      return (segments <= 1);
#else
      return (segments == 1); /* //drive is invalid on plain Windows */
#endif
    }
#endif

  /* directory is root if it's equal to '/' */
  if (len == 1 && dirent[0] == '/')
    return TRUE;

  return FALSE;
}