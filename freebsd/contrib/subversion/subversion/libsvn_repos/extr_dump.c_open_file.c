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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int dummy; } ;
struct dir_baton {int /*<<< orphan*/  cmp_rev; int /*<<< orphan*/  cmp_path; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ ARE_VALID_COPY_ARGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  dump_node (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_action_change ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_file(const char *path,
          void *parent_baton,
          svn_revnum_t ancestor_revision,
          apr_pool_t *pool,
          void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  const char *cmp_path = NULL;
  svn_revnum_t cmp_rev = SVN_INVALID_REVNUM;

  /* If the parent directory has explicit comparison path and rev,
     record the same for this one. */
  if (ARE_VALID_COPY_ARGS(pb->cmp_path, pb->cmp_rev))
    {
      cmp_path = svn_relpath_join(pb->cmp_path,
                                  svn_relpath_basename(path, pool), pool);
      cmp_rev = pb->cmp_rev;
    }

  SVN_ERR(dump_node(eb, path,
                    svn_node_file, svn_node_action_change,
                    FALSE, cmp_path, cmp_rev, pool));

  *file_baton = NULL;  /* muhahahaha again */
  return SVN_NO_ERROR;
}