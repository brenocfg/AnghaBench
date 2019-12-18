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
struct TYPE_4__ {int /*<<< orphan*/  const* id; int /*<<< orphan*/  copyroot_rev; int /*<<< orphan*/  created_path; scalar_t__ copyroot_path; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_copy_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_node_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_rev (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_txn_create (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__create_successor(const svn_fs_id_t **new_id_p,
                            svn_fs_t *fs,
                            const svn_fs_id_t *old_idp,
                            node_revision_t *new_noderev,
                            const svn_fs_fs__id_part_t *copy_id,
                            const svn_fs_fs__id_part_t *txn_id,
                            apr_pool_t *pool)
{
  const svn_fs_id_t *id;

  if (! copy_id)
    copy_id = svn_fs_fs__id_copy_id(old_idp);
  id = svn_fs_fs__id_txn_create(svn_fs_fs__id_node_id(old_idp), copy_id,
                                txn_id, pool);

  new_noderev->id = id;

  if (! new_noderev->copyroot_path)
    {
      new_noderev->copyroot_path = apr_pstrdup(pool,
                                               new_noderev->created_path);
      new_noderev->copyroot_rev = svn_fs_fs__id_rev(new_noderev->id);
    }

  SVN_ERR(svn_fs_fs__put_node_revision(fs, new_noderev->id, new_noderev, FALSE,
                                       pool));

  *new_id_p = id;

  return SVN_NO_ERROR;
}