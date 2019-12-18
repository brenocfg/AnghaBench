#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  txn_flags; int /*<<< orphan*/  pool; int /*<<< orphan*/  txn; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* make_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_root_t *
make_txn_root(svn_fs_t *fs,
              const char *txn,
              svn_revnum_t base_rev,
              apr_uint32_t flags,
              apr_pool_t *pool)
{
  svn_fs_root_t *root = make_root(fs, pool);
  root->is_txn_root = TRUE;
  root->txn = apr_pstrdup(root->pool, txn);
  root->txn_flags = flags;
  root->rev = base_rev;

  return root;
}