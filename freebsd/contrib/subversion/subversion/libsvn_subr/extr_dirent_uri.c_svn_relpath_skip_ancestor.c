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
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relpath_is_canonical (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

const char *
svn_relpath_skip_ancestor(const char *parent_relpath,
                          const char *child_relpath)
{
  apr_size_t len = strlen(parent_relpath);

  assert(relpath_is_canonical(parent_relpath));
  assert(relpath_is_canonical(child_relpath));

  if (len == 0)
    return child_relpath;

  if (0 != strncmp(parent_relpath, child_relpath, len))
    return NULL; /* parent_relpath is no ancestor of child_relpath */

  if (child_relpath[len] == 0)
    return ""; /* parent_relpath == child_relpath */

  if (child_relpath[len] == '/')
    return child_relpath + len + 1;

  return NULL;
}