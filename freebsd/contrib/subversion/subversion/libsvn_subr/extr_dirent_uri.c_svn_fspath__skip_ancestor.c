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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char const*) ; 
 char const* svn_relpath_skip_ancestor (char const*,char const*) ; 

const char *
svn_fspath__skip_ancestor(const char *parent_fspath,
                          const char *child_fspath)
{
  assert(svn_fspath__is_canonical(parent_fspath));
  assert(svn_fspath__is_canonical(child_fspath));

  return svn_relpath_skip_ancestor(parent_fspath + 1, child_fspath + 1);
}