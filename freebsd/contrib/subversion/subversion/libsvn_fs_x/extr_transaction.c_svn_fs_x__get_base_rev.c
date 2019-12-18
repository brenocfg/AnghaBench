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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_3__ {int /*<<< orphan*/  base_rev; } ;
typedef  TYPE_1__ svn_fs_x__transaction_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__get_txn (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_base_rev(svn_revnum_t *revnum,
                       svn_fs_t *fs,
                       svn_fs_x__txn_id_t txn_id,
                       apr_pool_t *scratch_pool)
{
  svn_fs_x__transaction_t *txn;
  SVN_ERR(svn_fs_x__get_txn(&txn, fs, txn_id, scratch_pool));
  *revnum = txn->base_rev;

  return SVN_NO_ERROR;
}