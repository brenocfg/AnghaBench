#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_13__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_FS__ITEM_TYPE_NODEREV ; 
 int /*<<< orphan*/  dbg_log_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* get_node_revision_body (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_error_createf (scalar_t__,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_2__* svn_fs_fs__id_rev_item (int /*<<< orphan*/  const*) ; 
 TYPE_1__* svn_fs_fs__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__get_node_revision(node_revision_t **noderev_p,
                             svn_fs_t *fs,
                             const svn_fs_id_t *id,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  const svn_fs_fs__id_part_t *rev_item = svn_fs_fs__id_rev_item(id);

  svn_error_t *err = get_node_revision_body(noderev_p, fs, id,
                                            result_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_FS_CORRUPT)
    {
      svn_string_t *id_string = svn_fs_fs__id_unparse(id, scratch_pool);
      return svn_error_createf(SVN_ERR_FS_CORRUPT, err,
                               "Corrupt node-revision '%s'",
                               id_string->data);
    }

  SVN_ERR(dbg_log_access(fs,
                         rev_item->revision,
                         rev_item->number,
                         *noderev_p,
                         SVN_FS_FS__ITEM_TYPE_NODEREV,
                         scratch_pool));

  return svn_error_trace(err);
}