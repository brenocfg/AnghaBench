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
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_7__ {char* id; int /*<<< orphan*/  base_rev; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_root_args {TYPE_2__* txn; int /*<<< orphan*/ ** root_p; } ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * make_txn_root (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__get_txn_ids (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__txn_proplist_in_trail (int /*<<< orphan*/ **,char const*,TYPE_1__*) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_txn_root(void *baton,
                  trail_t *trail)
{
  struct txn_root_args *args = baton;
  svn_fs_root_t **root_p = args->root_p;
  svn_fs_txn_t *txn = args->txn;
  svn_fs_t *fs = txn->fs;
  const char *svn_txn_id = txn->id;
  const svn_fs_id_t *root_id, *base_root_id;
  svn_fs_root_t *root;
  apr_hash_t *txnprops;
  apr_uint32_t flags = 0;

  /* Verify that the transaction actually exists.  */
  SVN_ERR(svn_fs_base__get_txn_ids(&root_id, &base_root_id, fs,
                                   svn_txn_id, trail, trail->pool));

  /* Look for special txn props that represent the 'flags' behavior of
     the transaction. */
  SVN_ERR(svn_fs_base__txn_proplist_in_trail(&txnprops, svn_txn_id, trail));
  if (svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CHECK_OOD))
    flags |= SVN_FS_TXN_CHECK_OOD;

  if (svn_hash_gets(txnprops, SVN_FS__PROP_TXN_CHECK_LOCKS))
    flags |= SVN_FS_TXN_CHECK_LOCKS;

  root = make_txn_root(fs, svn_txn_id, txn->base_rev, flags, trail->pool);

  *root_p = root;
  return SVN_NO_ERROR;
}