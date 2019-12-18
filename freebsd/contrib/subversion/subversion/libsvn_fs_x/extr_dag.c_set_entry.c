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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  node_pool; int /*<<< orphan*/  fs; int /*<<< orphan*/ * node_revision; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__set_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__update_dag_cache (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
set_entry(dag_node_t *parent,
          const char *name,
          const svn_fs_x__id_t *id,
          svn_node_kind_t kind,
          svn_fs_x__txn_id_t txn_id,
          apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t *parent_noderev = parent->node_revision;

  /* Set the new entry. */
  SVN_ERR(svn_fs_x__set_entry(parent->fs, txn_id, parent_noderev, name, id,
                              kind, parent->node_pool, scratch_pool));

  /* Update cached data. */
  svn_fs_x__update_dag_cache(parent);

  return SVN_NO_ERROR;
}