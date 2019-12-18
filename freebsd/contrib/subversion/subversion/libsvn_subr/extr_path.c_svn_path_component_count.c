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
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_canonical (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

apr_size_t
svn_path_component_count(const char *path)
{
  apr_size_t count = 0;

  assert(is_canonical(path, strlen(path)));

  while (*path)
    {
      const char *start;

      while (*path == '/')
        ++path;

      start = path;

      while (*path && *path != '/')
        ++path;

      if (path != start)
        ++count;
    }

  return count;
}