#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct get_dirents_args {int /*<<< orphan*/ ** dirents; int /*<<< orphan*/  txn_id; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_base__dag_node_kind (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

__attribute__((used)) static svn_error_t *
txn_body_get_dirents(void *baton, trail_t *trail)
{
  struct get_dirents_args *args = baton;
  dag_node_t *node;

  /* Get the node. */
  SVN_ERR(svn_fs_base__dag_get_node(&node, trail->fs, args->id,
                                    trail, trail->pool));

  /* If immutable, do nothing and return. */
  if (! svn_fs_base__dag_check_mutable(node, args->txn_id))
    return SVN_NO_ERROR;

  /* If a directory, do nothing and return. */
  *(args->dirents) = NULL;
  if (svn_fs_base__dag_node_kind(node) != svn_node_dir)
    return SVN_NO_ERROR;

  /* Else it's mutable.  Get its dirents. */
  return svn_fs_base__dag_dir_entries(args->dirents, node,
                                      trail, trail->pool);
}