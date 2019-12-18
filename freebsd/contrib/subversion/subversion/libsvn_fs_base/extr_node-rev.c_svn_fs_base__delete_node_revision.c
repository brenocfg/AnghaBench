#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_2__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT ; 
 int /*<<< orphan*/  svn_fs_base__id_node_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_bdb__delete_node_origin (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_bdb__delete_nodes_entry (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__delete_node_revision(svn_fs_t *fs,
                                  const svn_fs_id_t *id,
                                  svn_boolean_t origin_also,
                                  trail_t *trail,
                                  apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;

  /* ### todo: here, we should adjust other nodes to compensate for
     the missing node. */

  /* Delete the node origin record, too, if asked to do so and our
     format supports it. */
  if (origin_also && (bfd->format >= SVN_FS_BASE__MIN_NODE_ORIGINS_FORMAT))
    {
      SVN_ERR(svn_fs_bdb__delete_node_origin(fs, svn_fs_base__id_node_id(id),
                                             trail, pool));
    }

  return svn_fs_bdb__delete_nodes_entry(fs, id, trail, pool);
}