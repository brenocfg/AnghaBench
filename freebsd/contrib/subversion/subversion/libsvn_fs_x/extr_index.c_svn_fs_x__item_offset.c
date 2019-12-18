#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  l2p_index_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2p_proto_index_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__item_offset(apr_off_t *absolute_position,
                      apr_uint32_t *sub_item,
                      svn_fs_t *fs,
                      svn_fs_x__revision_file_t *rev_file,
                      const svn_fs_x__id_t *item_id,
                      apr_pool_t *scratch_pool)
{
  if (svn_fs_x__is_txn(item_id->change_set))
    SVN_ERR(l2p_proto_index_lookup(absolute_position, sub_item, fs,
                                   svn_fs_x__get_txn_id(item_id->change_set),
                                   item_id->number, scratch_pool));
  else
    SVN_ERR(l2p_index_lookup(absolute_position, sub_item, fs, rev_file,
                             svn_fs_x__get_revnum(item_id->change_set),
                             item_id->number, scratch_pool));

  return SVN_NO_ERROR;
}