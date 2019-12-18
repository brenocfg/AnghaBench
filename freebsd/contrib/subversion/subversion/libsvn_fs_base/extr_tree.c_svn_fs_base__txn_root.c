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
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_root_args {TYPE_1__* txn; int /*<<< orphan*/ ** root_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct txn_root_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_txn_root ; 

svn_error_t *
svn_fs_base__txn_root(svn_fs_root_t **root_p,
                      svn_fs_txn_t *txn,
                      apr_pool_t *pool)
{
  svn_fs_root_t *root;
  struct txn_root_args args;

  args.root_p = &root;
  args.txn = txn;
  SVN_ERR(svn_fs_base__retry_txn(txn->fs, txn_body_txn_root, &args,
                                 FALSE, pool));

  *root_p = root;
  return SVN_NO_ERROR;
}