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
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct lock_token_get_args {int /*<<< orphan*/ ** lock_p; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs__check_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lock_token_get_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_get_lock ; 

svn_error_t *
svn_fs_base__get_lock(svn_lock_t **lock,
                      svn_fs_t *fs,
                      const char *path,
                      apr_pool_t *pool)
{
  struct lock_token_get_args args;

  SVN_ERR(svn_fs__check_fs(fs, TRUE));

  args.path = svn_fs__canonicalize_abspath(path, pool);
  args.lock_p = lock;
  return svn_fs_base__retry_txn(fs, txn_body_get_lock, &args, FALSE, pool);
}