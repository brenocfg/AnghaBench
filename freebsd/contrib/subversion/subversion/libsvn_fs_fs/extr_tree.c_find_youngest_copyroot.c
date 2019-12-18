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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  node; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_copyroot (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
find_youngest_copyroot(svn_revnum_t *rev_p,
                       const char **path_p,
                       svn_fs_t *fs,
                       parent_path_t *parent_path,
                       apr_pool_t *pool)
{
  svn_revnum_t rev_mine;
  svn_revnum_t rev_parent = SVN_INVALID_REVNUM;
  const char *path_mine;
  const char *path_parent = NULL;

  /* First find our parent's youngest copyroot. */
  if (parent_path->parent)
    SVN_ERR(find_youngest_copyroot(&rev_parent, &path_parent, fs,
                                   parent_path->parent, pool));

  /* Find our copyroot. */
  SVN_ERR(svn_fs_fs__dag_get_copyroot(&rev_mine, &path_mine,
                                      parent_path->node));

  /* If a parent and child were copied to in the same revision, prefer
     the child copy target, since it is the copy relevant to the
     history of the child. */
  if (rev_mine >= rev_parent)
    {
      *rev_p = rev_mine;
      *path_p = path_mine;
    }
  else
    {
      *rev_p = rev_parent;
      *path_p = path_parent;
    }

  return SVN_NO_ERROR;
}