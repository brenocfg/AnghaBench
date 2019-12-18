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
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct paths_changed_args {int /*<<< orphan*/ * changes; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__retry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct paths_changed_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_paths_changed ; 

__attribute__((used)) static svn_error_t *
base_paths_changed(apr_hash_t **changed_paths_p,
                   svn_fs_root_t *root,
                   apr_pool_t *pool)
{
  struct paths_changed_args args;
  args.root = root;
  args.changes = NULL;
  SVN_ERR(svn_fs_base__retry(root->fs, txn_body_paths_changed, &args,
                             FALSE, pool));
  *changed_paths_p = args.changes;
  return SVN_NO_ERROR;
}