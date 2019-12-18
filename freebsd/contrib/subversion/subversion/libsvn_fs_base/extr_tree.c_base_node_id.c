#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_id_args {char const* path; TYPE_1__* root; int /*<<< orphan*/  const** id_p; } ;
struct TYPE_5__ {int /*<<< orphan*/  root_dir; } ;
typedef  TYPE_2__ base_root_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct node_id_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_node_id ; 

__attribute__((used)) static svn_error_t *
base_node_id(const svn_fs_id_t **id_p,
             svn_fs_root_t *root,
             const char *path,
             apr_pool_t *pool)
{
  base_root_data_t *brd = root->fsap_data;

  if (! root->is_txn_root
      && (path[0] == '\0' || ((path[0] == '/') && (path[1] == '\0'))))
    {
      /* Optimize the case where we don't need any db access at all.
         The root directory ("" or "/") node is stored in the
         svn_fs_root_t object, and never changes when it's a revision
         root, so we can just reach in and grab it directly. */
      *id_p = svn_fs_base__id_copy(svn_fs_base__dag_get_id(brd->root_dir),
                                   pool);
    }
  else
    {
      const svn_fs_id_t *id;
      struct node_id_args args;

      args.id_p = &id;
      args.root = root;
      args.path = path;

      SVN_ERR(svn_fs_base__retry_txn(root->fs, txn_body_node_id, &args,
                                     FALSE, pool));
      *id_p = id;
    }
  return SVN_NO_ERROR;
}