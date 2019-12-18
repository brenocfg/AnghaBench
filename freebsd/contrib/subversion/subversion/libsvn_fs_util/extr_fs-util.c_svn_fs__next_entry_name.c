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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 

char *
svn_fs__next_entry_name(const char **next_p,
                        const char *path,
                        apr_pool_t *pool)
{
  const char *end;

  /* Find the end of the current component.  */
  end = strchr(path, '/');

  if (! end)
    {
      /* The path contains only one component, with no trailing
         slashes. */
      *next_p = 0;
      return apr_pstrdup(pool, path);
    }
  else
    {
      /* There's a slash after the first component.  Skip over an arbitrary
         number of slashes to find the next one. */
      const char *next = end;
      while (*next == '/')
        next++;
      *next_p = next;
      return apr_pstrndup(pool, path, end - path);
    }
}