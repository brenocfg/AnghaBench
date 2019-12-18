#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  predecessor_count; int /*<<< orphan*/  predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_check_mutable (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__put_node_revision (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_update_ancestry(dag_node_t *target,
                               dag_node_t *source,
                               apr_pool_t *pool)
{
  node_revision_t *source_noderev, *target_noderev;

  if (! svn_fs_fs__dag_check_mutable(target))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to update ancestry of non-mutable node"));

  SVN_ERR(get_node_revision(&source_noderev, source));
  SVN_ERR(get_node_revision(&target_noderev, target));

  target_noderev->predecessor_id = source->id;
  target_noderev->predecessor_count = source_noderev->predecessor_count;
  target_noderev->predecessor_count++;

  return svn_fs_fs__put_node_revision(target->fs, target->id, target_noderev,
                                      FALSE, pool);
}