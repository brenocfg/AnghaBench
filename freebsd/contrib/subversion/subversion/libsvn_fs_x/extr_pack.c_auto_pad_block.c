#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/ * items; scalar_t__ item_count; scalar_t__ fnv1_checksum; int /*<<< orphan*/  type; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ svn_fs_x__p2l_entry_t ;
struct TYPE_10__ {int block_size; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  pack_offset; int /*<<< orphan*/  proto_p2l_index; int /*<<< orphan*/  pack_file; TYPE_1__* fs; } ;
typedef  TYPE_4__ pack_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ const apr_off_t ;
struct TYPE_8__ {TYPE_3__* fsap_data; } ;

/* Variables and functions */
 scalar_t__ MAX (int,int) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_TYPE_UNUSED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ get_block_left (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_fs_x__p2l_proto_index_add_entry (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_null_bytes (int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
auto_pad_block(pack_context_t *context,
               apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = context->fs->fsap_data;

  /* This is the maximum number of bytes "wasted" that way per block.
   * Larger items will cross the block boundaries. */
  const apr_off_t max_padding = MAX(ffd->block_size / 50, 512);

  /* Is wasted space small enough to align the current item to the next
   * block? */
  apr_off_t padding = get_block_left(context);

  if (padding < max_padding)
    {
      /* Yes. To up with NUL bytes and don't forget to create
       * an P2L index entry marking this section as unused. */
      svn_fs_x__p2l_entry_t null_entry;

      null_entry.offset = context->pack_offset;
      null_entry.size = padding;
      null_entry.type = SVN_FS_X__ITEM_TYPE_UNUSED;
      null_entry.fnv1_checksum = 0;
      null_entry.item_count = 0;
      null_entry.items = NULL;

      SVN_ERR(write_null_bytes(context->pack_file, padding, scratch_pool));
      SVN_ERR(svn_fs_x__p2l_proto_index_add_entry
                  (context->proto_p2l_index, &null_entry, scratch_pool));
      context->pack_offset += padding;
    }

  return SVN_NO_ERROR;
}