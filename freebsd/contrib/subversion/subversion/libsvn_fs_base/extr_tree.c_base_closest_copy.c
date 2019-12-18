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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct closest_copy_args {char const** path_p; char const* path; int /*<<< orphan*/ * pool; TYPE_1__* root; TYPE_1__** root_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct closest_copy_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_closest_copy ; 

__attribute__((used)) static svn_error_t *
base_closest_copy(svn_fs_root_t **root_p,
                  const char **path_p,
                  svn_fs_root_t *root,
                  const char *path,
                  apr_pool_t *pool)
{
  struct closest_copy_args args;
  svn_fs_t *fs = root->fs;
  svn_fs_root_t *closest_root = NULL;
  const char *closest_path = NULL;

  args.root_p = &closest_root;
  args.path_p = &closest_path;
  args.root = root;
  args.path = path;
  args.pool = pool;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_closest_copy, &args,
                                 FALSE, pool));
  *root_p = closest_root;
  *path_p = closest_path;
  return SVN_NO_ERROR;
}