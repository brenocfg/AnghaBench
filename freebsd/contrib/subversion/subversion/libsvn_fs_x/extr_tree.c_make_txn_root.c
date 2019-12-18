#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_6__ {TYPE_2__* fsap_data; int /*<<< orphan*/  rev; int /*<<< orphan*/  txn_flags; int /*<<< orphan*/  pool; int /*<<< orphan*/  txn; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_2__ fs_txn_root_data_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* make_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
make_txn_root(svn_fs_root_t **root_p,
              svn_fs_t *fs,
              svn_fs_x__txn_id_t txn_id,
              svn_revnum_t base_rev,
              apr_uint32_t flags,
              apr_pool_t *result_pool)
{
  svn_fs_root_t *root = make_root(fs, result_pool);
  fs_txn_root_data_t *frd = apr_pcalloc(root->pool, sizeof(*frd));
  frd->txn_id = txn_id;

  root->is_txn_root = TRUE;
  root->txn = svn_fs_x__txn_name(txn_id, root->pool);
  root->txn_flags = flags;
  root->rev = base_rev;
  root->fsap_data = frd;

  *root_p = root;
  return SVN_NO_ERROR;
}