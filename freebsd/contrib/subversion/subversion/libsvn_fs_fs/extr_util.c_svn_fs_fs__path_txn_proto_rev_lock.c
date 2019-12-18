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
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
struct TYPE_7__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_EXT_REV_LOCK ; 
 int /*<<< orphan*/  PATH_REV_LOCK ; 
 scalar_t__ SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT ; 
 int /*<<< orphan*/  combine_txn_id_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_dir (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_proto_revs (TYPE_1__*,int /*<<< orphan*/ *) ; 

const char *
svn_fs_fs__path_txn_proto_rev_lock(svn_fs_t *fs,
                                   const svn_fs_fs__id_part_t *txn_id,
                                   apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  if (ffd->format >= SVN_FS_FS__MIN_PROTOREVS_DIR_FORMAT)
    return svn_dirent_join(svn_fs_fs__path_txn_proto_revs(fs, pool),
                           combine_txn_id_string(txn_id, PATH_EXT_REV_LOCK,
                                                 pool),
                           pool);
  else
    return svn_dirent_join(svn_fs_fs__path_txn_dir(fs, txn_id, pool),
                           PATH_REV_LOCK, pool);
}