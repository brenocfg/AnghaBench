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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  predecessor_count; int /*<<< orphan*/  predecessor_id; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__get_node_revision (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_copy_id (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_fs__id_is_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_node_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_create (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_new_txn_noderev_from_rev(svn_fs_t *fs,
                                const svn_fs_fs__id_part_t *txn_id,
                                svn_fs_id_t *src,
                                apr_pool_t *pool)
{
  node_revision_t *noderev;
  const svn_fs_fs__id_part_t *node_id, *copy_id;

  SVN_ERR(svn_fs_fs__get_node_revision(&noderev, fs, src, pool, pool));

  if (svn_fs_fs__id_is_txn(noderev->id))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Copying from transactions not allowed"));

  noderev->predecessor_id = noderev->id;
  noderev->predecessor_count++;
  noderev->copyfrom_path = NULL;
  noderev->copyfrom_rev = SVN_INVALID_REVNUM;

  /* For the transaction root, the copyroot never changes. */

  node_id = svn_fs_fs__id_node_id(noderev->id);
  copy_id = svn_fs_fs__id_copy_id(noderev->id);
  noderev->id = svn_fs_fs__id_txn_create(node_id, copy_id, txn_id, pool);

  return svn_fs_fs__put_node_revision(fs, noderev->id, noderev, TRUE, pool);
}