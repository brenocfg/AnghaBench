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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct revision_proplist_args {int /*<<< orphan*/  rev; int /*<<< orphan*/ ** table_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct revision_proplist_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_revision_proplist ; 

svn_error_t *
svn_fs_base__revision_proplist(apr_hash_t **table_p,
                               svn_fs_t *fs,
                               svn_revnum_t rev,
                               svn_boolean_t refresh,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  struct revision_proplist_args args;
  apr_hash_t *table;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.table_p = &table;
  args.rev = rev;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_revision_proplist, &args,
                                 FALSE, result_pool));

  *table_p = table ? table : apr_hash_make(result_pool);
  return SVN_NO_ERROR;
}