#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/ * copyroot_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  created_path; int /*<<< orphan*/  predecessor_count; int /*<<< orphan*/  predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_15__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* copy_node_revision (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__create_successor (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_created_path (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_fs (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_get_id (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_set_entry (TYPE_2__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__reserve_copy_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_copy(dag_node_t *to_node,
                    const char *entry,
                    dag_node_t *from_node,
                    svn_boolean_t preserve_history,
                    svn_revnum_t from_rev,
                    const char *from_path,
                    const svn_fs_fs__id_part_t *txn_id,
                    apr_pool_t *pool)
{
  const svn_fs_id_t *id;

  if (preserve_history)
    {
      node_revision_t *from_noderev, *to_noderev;
      svn_fs_fs__id_part_t copy_id;
      const svn_fs_id_t *src_id = svn_fs_fs__dag_get_id(from_node);
      svn_fs_t *fs = svn_fs_fs__dag_get_fs(from_node);

      /* Make a copy of the original node revision. */
      SVN_ERR(get_node_revision(&from_noderev, from_node));
      to_noderev = copy_node_revision(from_noderev, pool);

      /* Reserve a copy ID for this new copy. */
      SVN_ERR(svn_fs_fs__reserve_copy_id(&copy_id, fs, txn_id, pool));

      /* Create a successor with its predecessor pointing at the copy
         source. */
      to_noderev->predecessor_id = svn_fs_fs__id_copy(src_id, pool);
      to_noderev->predecessor_count++;
      to_noderev->created_path =
        svn_fspath__join(svn_fs_fs__dag_get_created_path(to_node), entry,
                     pool);
      to_noderev->copyfrom_path = apr_pstrdup(pool, from_path);
      to_noderev->copyfrom_rev = from_rev;

      /* Set the copyroot equal to our own id. */
      to_noderev->copyroot_path = NULL;

      SVN_ERR(svn_fs_fs__create_successor(&id, fs, src_id, to_noderev,
                                          &copy_id, txn_id, pool));

    }
  else  /* don't preserve history */
    {
      id = svn_fs_fs__dag_get_id(from_node);
    }

  /* Set the entry in to_node to the new id. */
  return svn_fs_fs__dag_set_entry(to_node, entry, id, from_node->kind,
                                  txn_id, pool);
}