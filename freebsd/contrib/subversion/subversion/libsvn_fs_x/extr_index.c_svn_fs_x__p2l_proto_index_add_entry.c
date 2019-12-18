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
struct TYPE_4__ {scalar_t__ offset; scalar_t__ size; size_t type; size_t fnv1_checksum; size_t item_count; TYPE_2__* items; } ;
typedef  TYPE_1__ svn_fs_x__p2l_entry_t ;
struct TYPE_5__ {scalar_t__ change_set; size_t number; } ;
typedef  TYPE_2__ svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  size_t apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  size_t apr_int32_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  write_uint64_to_proto_index (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__p2l_proto_index_add_entry(apr_file_t *proto_index,
                                    const svn_fs_x__p2l_entry_t *entry,
                                    apr_pool_t *scratch_pool)
{
  apr_uint64_t revision;
  apr_int32_t i;

  /* Make sure all signed elements of ENTRY have non-negative values.
   *
   * For file offsets and sizes, this is a given as we use them to describe
   * absolute positions and sizes.  For revisions, SVN_INVALID_REVNUM is
   * valid, hence we have to shift it by 1.
   */
  SVN_ERR_ASSERT(entry->offset >= 0);
  SVN_ERR_ASSERT(entry->size >= 0);

  /* Now, all values will nicely convert to uint64. */
  /* Make sure to keep P2L_PROTO_INDEX_ENTRY_SIZE consistent with this: */

  SVN_ERR(write_uint64_to_proto_index(proto_index, entry->offset,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry->size,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry->type,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry->fnv1_checksum,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry->item_count,
                                      scratch_pool));

  /* Add sub-items. */
  for (i = 0; i < entry->item_count; ++i)
    {
      const svn_fs_x__id_t *sub_item = &entry->items[i];

      /* Make sure all signed elements of ENTRY have non-negative values.
       *
       * For file offsets and sizes, this is a given as we use them to
       * describe absolute positions and sizes.  For revisions,
       * SVN_INVALID_REVNUM is valid, hence we have to shift it by 1.
      */
      SVN_ERR_ASSERT(   sub_item->change_set >= 0
                     || sub_item->change_set == SVN_INVALID_REVNUM);

      /* Write sub- record. */
      revision = sub_item->change_set == SVN_INVALID_REVNUM
               ? 0
               : ((apr_uint64_t)sub_item->change_set + 1);

      SVN_ERR(write_uint64_to_proto_index(proto_index, revision,
                                          scratch_pool));
      SVN_ERR(write_uint64_to_proto_index(proto_index, sub_item->number,
                                          scratch_pool));
    }

  /* Add trailer: rev / pack file offset of the next item */
  SVN_ERR(write_uint64_to_proto_index(proto_index,
                                      entry->offset + entry->size,
                                      scratch_pool));

  return SVN_NO_ERROR;
}