#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_7__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_8__ {scalar_t__ format; } ;
typedef  TYPE_2__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__id_node_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__new_node_id (int /*<<< orphan*/ **,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_node_revision (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__set_node_origin (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__create_node(const svn_fs_id_t **id_p,
                         svn_fs_t *fs,
                         node_revision_t *noderev,
                         const char *copy_id,
                         const char *txn_id,
                         trail_t *trail,
                         apr_pool_t *pool)
{
  svn_fs_id_t *id;
  base_fs_data_t *bfd = fs->fsap_data;

  /* Find an unused ID for the node.  */
  SVN_ERR(svn_fs_bdb__new_node_id(&id, fs, copy_id, txn_id, trail, pool));

  /* Store its NODE-REVISION skel.  */
  SVN_ERR(svn_fs_bdb__put_node_revision(fs, id, noderev, trail, pool));

  /* Add a record in the node origins index table if our format
     supports it.  */
  if (bfd->format >= SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT)
    {
      SVN_ERR(svn_fs_bdb__set_node_origin(fs, svn_fs_base__id_node_id(id),
                                          id, trail, pool));
    }

  *id_p = id;
  return SVN_NO_ERROR;
}