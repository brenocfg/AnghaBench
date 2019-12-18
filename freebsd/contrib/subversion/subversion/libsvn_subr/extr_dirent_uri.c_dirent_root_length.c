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
typedef  int apr_size_t ;

/* Variables and functions */

__attribute__((used)) static apr_size_t
dirent_root_length(const char *dirent, apr_size_t len)
{
#ifdef SVN_USE_DOS_PATHS
  if (len >= 2 && dirent[1] == ':' &&
      ((dirent[0] >= 'A' && dirent[0] <= 'Z') ||
       (dirent[0] >= 'a' && dirent[0] <= 'z')))
    {
      return (len > 2 && dirent[2] == '/') ? 3 : 2;
    }

  if (len > 2 && dirent[0] == '/' && dirent[1] == '/')
    {
      apr_size_t i = 2;

      while (i < len && dirent[i] != '/')
        i++;

      if (i == len)
        return len; /* Cygwin drive alias, invalid path on WIN32 */

      i++; /* Skip '/' */

      while (i < len && dirent[i] != '/')
        i++;

      return i;
    }
#endif /* SVN_USE_DOS_PATHS */
  if (len >= 1 && dirent[0] == '/')
    return 1;

  return 0;
}