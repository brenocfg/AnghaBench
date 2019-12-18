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
 char const SVN_PATH_LOCAL_SEPARATOR ; 
 int /*<<< orphan*/  TRUE ; 
 size_t strspn (char const*,char*) ; 

__attribute__((used)) static svn_boolean_t
repos_path_valid(const char *path)
{
  const char *s = path;

  while (*s)
    {
      /* Scan for the end of the segment. */
      while (*path && *path != '/' && *path != SVN_PATH_LOCAL_SEPARATOR)
        ++path;

      /* Check for '..'. */
#ifdef WIN32
      /* On Windows, don't allow sequences of more than one character
         consisting of just dots and spaces.  Win32 functions treat
         paths such as ".. " and "......." inconsistently.  Make sure
         no one can escape out of the root. */
      if (path - s >= 2 && strspn(s, ". ") == (size_t)(path - s))
        return FALSE;
#else  /* ! WIN32 */
      if (path - s == 2 && s[0] == '.' && s[1] == '.')
        return FALSE;
#endif

      /* Skip all separators. */
      while (*path && (*path == '/' || *path == SVN_PATH_LOCAL_SEPARATOR))
        ++path;
      s = path;
    }

  return TRUE;
}