#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_4__ {TYPE_2__ id; } ;
typedef  TYPE_1__ svn_fs_x__representation_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__item_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_open_proto_rev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
open_and_seek_transaction(svn_fs_x__revision_file_t **file,
                          svn_fs_t *fs,
                          svn_fs_x__representation_t *rep,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  apr_off_t offset;
  apr_uint32_t sub_item = 0;
  apr_int64_t txn_id = svn_fs_x__get_txn_id(rep->id.change_set);

  SVN_ERR(svn_fs_x__rev_file_open_proto_rev(file, fs, txn_id, result_pool,
                                            scratch_pool));

  SVN_ERR(svn_fs_x__item_offset(&offset, &sub_item, fs, *file, &rep->id,
                                scratch_pool));
  SVN_ERR(svn_fs_x__rev_file_seek(*file, NULL, offset));

  return SVN_NO_ERROR;
}