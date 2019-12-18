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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT ; 
 int /*<<< orphan*/  read_next_ids (scalar_t__*,scalar_t__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__write_current (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_final_current(svn_fs_t *fs,
                    const svn_fs_fs__id_part_t *txn_id,
                    svn_revnum_t rev,
                    apr_uint64_t start_node_id,
                    apr_uint64_t start_copy_id,
                    apr_pool_t *pool)
{
  apr_uint64_t txn_node_id;
  apr_uint64_t txn_copy_id;
  fs_fs_data_t *ffd = fs->fsap_data;

  if (ffd->format >= SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT)
    return svn_fs_fs__write_current(fs, rev, 0, 0, pool);

  /* To find the next available ids, we add the id that used to be in
     the 'current' file, to the next ids from the transaction file. */
  SVN_ERR(read_next_ids(&txn_node_id, &txn_copy_id, fs, txn_id, pool));

  start_node_id += txn_node_id;
  start_copy_id += txn_copy_id;

  return svn_fs_fs__write_current(fs, rev, start_node_id, start_copy_id,
                                  pool);
}