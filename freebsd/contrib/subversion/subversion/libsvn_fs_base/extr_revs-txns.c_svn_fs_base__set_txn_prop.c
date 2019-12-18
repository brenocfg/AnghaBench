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
struct TYPE_4__ {scalar_t__ kind; scalar_t__ proplist; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 char const* SVN_FS__PROP_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_txn (TYPE_1__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * put_txn (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_txn_not_mutable (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* svn_string_create (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ transaction_kind_normal ; 

svn_error_t *
svn_fs_base__set_txn_prop(svn_fs_t *fs,
                          const char *txn_name,
                          const char *name,
                          const svn_string_t *value,
                          trail_t *trail,
                          apr_pool_t *pool)
{
  transaction_t *txn;

  SVN_ERR(get_txn(&txn, fs, txn_name, FALSE, trail, pool));
  if (txn->kind != transaction_kind_normal)
    return svn_fs_base__err_txn_not_mutable(fs, txn_name);

  /* If there's no proplist, but we're just deleting a property, exit now. */
  if ((! txn->proplist) && (! value))
    return SVN_NO_ERROR;

  /* Now, if there's no proplist, we know we need to make one. */
  if (! txn->proplist)
    txn->proplist = apr_hash_make(pool);

  /* Set the property. */
  if (svn_hash_gets(txn->proplist, SVN_FS__PROP_TXN_CLIENT_DATE)
      && !strcmp(name, SVN_PROP_REVISION_DATE))
    svn_hash_sets(txn->proplist, SVN_FS__PROP_TXN_CLIENT_DATE,
                  svn_string_create("1", pool));
  svn_hash_sets(txn->proplist, name, value);

  /* Now overwrite the transaction. */
  return put_txn(fs, txn, txn_name, trail, pool);
}