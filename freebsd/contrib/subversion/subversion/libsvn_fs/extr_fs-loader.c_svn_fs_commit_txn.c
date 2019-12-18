#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_12__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_txn_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {TYPE_3__* (* commit ) (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_E (int,TYPE_3__*) ; 
 scalar_t__ SVN_ERR_FS_CONFLICT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 TYPE_3__* stub1 (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_commit_txn(const char **conflict_p, svn_revnum_t *new_rev,
                   svn_fs_txn_t *txn, apr_pool_t *pool)
{
  svn_error_t *err;

  *new_rev = SVN_INVALID_REVNUM;
  if (conflict_p)
    *conflict_p = NULL;

  err = txn->vtable->commit(conflict_p, new_rev, txn, pool);

#ifdef SVN_DEBUG
  /* Check postconditions. */
  if (conflict_p)
    {
      SVN_ERR_ASSERT_E(! (SVN_IS_VALID_REVNUM(*new_rev) && *conflict_p != NULL),
                       err);
      SVN_ERR_ASSERT_E((*conflict_p != NULL)
                       == (err && err->apr_err == SVN_ERR_FS_CONFLICT),
                       err);
    }
#endif

  SVN_ERR(err);

  return SVN_NO_ERROR;
}