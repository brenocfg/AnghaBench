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
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_node_revision (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__set_entry (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_entry(dag_node_t *parent,
          const char *name,
          const svn_fs_id_t *id,
          svn_node_kind_t kind,
          const svn_fs_fs__id_part_t *txn_id,
          apr_pool_t *pool)
{
  node_revision_t *parent_noderev;

  /* Get the parent's node-revision. */
  SVN_ERR(get_node_revision(&parent_noderev, parent));

  /* Set the new entry. */
  return svn_fs_fs__set_entry(parent->fs, txn_id, parent_noderev, name, id,
                              kind, pool);
}