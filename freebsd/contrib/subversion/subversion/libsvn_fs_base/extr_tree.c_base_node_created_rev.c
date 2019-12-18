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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_created_rev_args {char const* path; int /*<<< orphan*/  revision; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct node_created_rev_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_node_created_rev ; 

__attribute__((used)) static svn_error_t *
base_node_created_rev(svn_revnum_t *revision,
                      svn_fs_root_t *root,
                      const char *path,
                      apr_pool_t *pool)
{
  struct node_created_rev_args args;

  args.revision = SVN_INVALID_REVNUM;
  args.root = root;
  args.path = path;
  SVN_ERR(svn_fs_base__retry_txn
          (root->fs, txn_body_node_created_rev, &args, TRUE, pool));
  *revision = args.revision;
  return SVN_NO_ERROR;
}