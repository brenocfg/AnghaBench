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
struct TYPE_3__ {int /*<<< orphan*/  txn_name; int /*<<< orphan*/  txn; scalar_t__ rev_id; scalar_t__ is_revision; } ;
typedef  TYPE_1__ svnlook_ctxt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_txn_base_revision (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_base_rev(svn_revnum_t *base_rev, svnlook_ctxt_t *c, apr_pool_t *pool)
{
  if (c->is_revision)
    {
      *base_rev = c->rev_id - 1;
    }
  else
    {
      *base_rev = svn_fs_txn_base_revision(c->txn);

      if (! SVN_IS_VALID_REVNUM(*base_rev))
        return svn_error_createf
          (SVN_ERR_FS_NO_SUCH_REVISION, NULL,
           _("Transaction '%s' is not based on a revision; how odd"),
           c->txn_name);
    }
  return SVN_NO_ERROR;
}