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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int predecessor_count; int /*<<< orphan*/  const* predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_bdb__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_ancestry(svn_fs_t *fs,
                const svn_fs_id_t *source_id,
                const svn_fs_id_t *target_id,
                const char *txn_id,
                const char *target_path,
                int source_pred_count,
                trail_t *trail,
                apr_pool_t *pool)
{
  node_revision_t *noderev;

  /* Set target's predecessor-id to source_id.  */
  if (strcmp(svn_fs_base__id_txn_id(target_id), txn_id))
    return svn_error_createf
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Unexpected immutable node at '%s'"), target_path);
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, fs, target_id,
                                        trail, pool));
  noderev->predecessor_id = source_id;
  noderev->predecessor_count = source_pred_count;
  if (noderev->predecessor_count != -1)
    noderev->predecessor_count++;
  return svn_fs_bdb__put_node_revision(fs, target_id, noderev, trail, pool);
}