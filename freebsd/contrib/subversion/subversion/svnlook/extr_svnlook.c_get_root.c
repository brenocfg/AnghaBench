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
struct TYPE_3__ {int /*<<< orphan*/  txn; int /*<<< orphan*/  rev_id; int /*<<< orphan*/  fs; scalar_t__ is_revision; } ;
typedef  TYPE_1__ svnlook_ctxt_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_txn_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_root(svn_fs_root_t **root,
         svnlook_ctxt_t *c,
         apr_pool_t *pool)
{
  /* Open up the appropriate root (revision or transaction). */
  if (c->is_revision)
    {
      /* If we didn't get a valid revision number, we'll look at the
         youngest revision. */
      if (! SVN_IS_VALID_REVNUM(c->rev_id))
        SVN_ERR(svn_fs_youngest_rev(&(c->rev_id), c->fs, pool));

      SVN_ERR(svn_fs_revision_root(root, c->fs, c->rev_id, pool));
    }
  else
    {
      SVN_ERR(svn_fs_txn_root(root, c->txn, pool));
    }

  return SVN_NO_ERROR;
}