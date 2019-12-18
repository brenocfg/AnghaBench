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
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct begin_txn_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  base_rev; int /*<<< orphan*/ ** txn_p; } ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct begin_txn_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_begin_txn ; 

svn_error_t *
svn_fs_base__begin_txn(svn_fs_txn_t **txn_p,
                       svn_fs_t *fs,
                       svn_revnum_t rev,
                       apr_uint32_t flags,
                       apr_pool_t *pool)
{
  svn_fs_txn_t *txn;
  struct begin_txn_args args;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.txn_p = &txn;
  args.base_rev = rev;
  args.flags = flags;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_begin_txn, &args, FALSE, pool));

  *txn_p = txn;

  return SVN_NO_ERROR;
}