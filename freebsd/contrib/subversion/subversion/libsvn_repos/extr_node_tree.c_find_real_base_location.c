#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {char action; char* copyfrom_path; int /*<<< orphan*/  name; struct TYPE_3__* parent; int /*<<< orphan*/  copyfrom_rev; } ;
typedef  TYPE_1__ svn_repos_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 char* svn_fspath__join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
find_real_base_location(const char **path_p,
                        svn_revnum_t *rev_p,
                        svn_repos_node_t *node,
                        apr_pool_t *pool)
{
  /* If NODE is an add-with-history, then its real base location is
     the copy source. */
  if ((node->action == 'A')
      && node->copyfrom_path
      && SVN_IS_VALID_REVNUM(node->copyfrom_rev))
    {
      *path_p = node->copyfrom_path;
      *rev_p = node->copyfrom_rev;
      return;
    }

  /* Otherwise, if NODE has a parent, we'll recurse, and add NODE's
     name to whatever the parent's real base path turns out to be (and
     pass the base revision on through). */
  if (node->parent)
    {
      const char *path;
      svn_revnum_t rev;

      find_real_base_location(&path, &rev, node->parent, pool);
      *path_p = svn_fspath__join(path, node->name, pool);
      *rev_p = rev;
      return;
    }

  /* Finally, if the node has no parent, then its name is "/", and it
     has no interesting base revision.  */
  *path_p = "/";
  *rev_p = SVN_INVALID_REVNUM;
  return;
}