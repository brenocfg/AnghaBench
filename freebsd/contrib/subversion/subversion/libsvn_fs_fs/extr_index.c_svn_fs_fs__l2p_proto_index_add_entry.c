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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int offset; int item_index; } ;
typedef  TYPE_1__ l2p_proto_entry_t ;
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int UINT_MAX ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_l2p_entry_to_proto_index (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__l2p_proto_index_add_entry(apr_file_t *proto_index,
                                     apr_off_t offset,
                                     apr_uint64_t item_index,
                                     apr_pool_t *scratch_pool)
{
  l2p_proto_entry_t entry;

  /* make sure the conversion to uint64 works */
  SVN_ERR_ASSERT(offset >= -1);

  /* we support offset '-1' as a "not used" indication */
  entry.offset = (apr_uint64_t)offset + 1;

  /* make sure we can use item_index as an array index when building the
   * final index file */
  SVN_ERR_ASSERT(item_index < UINT_MAX / 2);
  entry.item_index = item_index;

  return svn_error_trace(write_l2p_entry_to_proto_index(proto_index, entry,
                                                        scratch_pool));
}