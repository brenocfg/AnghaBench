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
struct node_created_path_args {char const** created_path; char const* path; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct node_created_path_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_node_created_path ; 

__attribute__((used)) static svn_error_t *
base_node_created_path(const char **created_path,
                       svn_fs_root_t *root,
                       const char *path,
                       apr_pool_t *pool)
{
  struct node_created_path_args args;
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  args.created_path = created_path;
  args.root = root;
  args.path = path;

  SVN_ERR(svn_fs_base__retry_txn(root->fs, txn_body_node_created_path, &args,
                                 FALSE, scratch_pool));
  if (*created_path)
    *created_path = apr_pstrdup(pool, *created_path);
  svn_pool_destroy(scratch_pool);
  return SVN_NO_ERROR;
}