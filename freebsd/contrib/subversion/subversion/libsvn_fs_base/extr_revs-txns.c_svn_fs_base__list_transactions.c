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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct list_transactions_args {int /*<<< orphan*/ * pool; int /*<<< orphan*/ ** names_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__retry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct list_transactions_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_list_transactions ; 

svn_error_t *
svn_fs_base__list_transactions(apr_array_header_t **names_p,
                               svn_fs_t *fs,
                               apr_pool_t *pool)
{
  apr_array_header_t *names;
  struct list_transactions_args args;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.names_p = &names;
  args.pool = pool;
  SVN_ERR(svn_fs_base__retry(fs, txn_body_list_transactions, &args,
                             FALSE, pool));

  *names_p = names;
  return SVN_NO_ERROR;
}