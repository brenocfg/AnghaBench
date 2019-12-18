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
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_open_txn (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_hash_to_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_change_txn_props (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_revprops(svn_fs_t *fs,
               const char *txn_name,
               apr_hash_t *revprops,
               apr_pool_t *scratch_pool)
{
  svn_fs_txn_t *txn;
  const apr_array_header_t *revprops_array;

  /* The FS editor has a TXN inside it, but we can't access it. Open another
     based on the TXN_NAME.  */
  SVN_ERR(svn_fs_open_txn(&txn, fs, txn_name, scratch_pool));

  /* Validate and apply the revision properties.  */
  revprops_array = svn_prop_hash_to_array(revprops, scratch_pool);
  SVN_ERR(svn_repos_fs_change_txn_props(txn, revprops_array, scratch_pool));

  /* ### do we need to force the txn to close, or is it enough to wait
     ### for the pool to be cleared?  */
  return SVN_NO_ERROR;
}