#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_5__* fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_deltify_args {int /*<<< orphan*/  txn_id; int /*<<< orphan*/  is_dir; scalar_t__ base_id; scalar_t__ tgt_id; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_9__ {scalar_t__ format; } ;
typedef  TYPE_2__ base_fs_data_t ;
struct TYPE_10__ {TYPE_2__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_BASE__MIN_REP_SHARING_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_deltify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,TYPE_5__*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_index_checksums (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_txn_deltify(void *baton, trail_t *trail)
{
  struct txn_deltify_args *args = baton;
  dag_node_t *tgt_node, *base_node;
  base_fs_data_t *bfd = trail->fs->fsap_data;

  SVN_ERR(svn_fs_base__dag_get_node(&tgt_node, trail->fs, args->tgt_id,
                                    trail, trail->pool));
  /* If we have something to deltify against, do so. */
  if (args->base_id)
    {
      SVN_ERR(svn_fs_base__dag_get_node(&base_node, trail->fs, args->base_id,
                                        trail, trail->pool));
      SVN_ERR(svn_fs_base__dag_deltify(tgt_node, base_node, args->is_dir,
                                       args->txn_id, trail, trail->pool));
    }

  /* If we support rep sharing, and this isn't a directory, record a
     mapping of TGT_NODE's data checksum to its representation key. */
  if (bfd->format >= SVN_FS_BASE__MIN_REP_SHARING_FORMAT)
    SVN_ERR(svn_fs_base__dag_index_checksums(tgt_node, trail, trail->pool));

  return SVN_NO_ERROR;
}