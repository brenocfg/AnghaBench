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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {scalar_t__ item_index; int /*<<< orphan*/  sub_item; scalar_t__ offset; } ;
typedef  TYPE_1__ l2p_proto_entry_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_l2p_entry_from_proto_index (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_l2p_proto_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
l2p_proto_index_lookup(apr_off_t *offset,
                       apr_uint32_t *sub_item,
                       svn_fs_t *fs,
                       svn_fs_x__txn_id_t txn_id,
                       apr_uint64_t item_index,
                       apr_pool_t *scratch_pool)
{
  svn_boolean_t eof = FALSE;
  apr_file_t *file = NULL;
  SVN_ERR(svn_io_file_open(&file,
                           svn_fs_x__path_l2p_proto_index(fs, txn_id,
                                                          scratch_pool),
                           APR_READ | APR_BUFFERED, APR_OS_DEFAULT,
                           scratch_pool));

  /* process all entries until we fail due to EOF */
  *offset = -1;
  while (!eof)
    {
      l2p_proto_entry_t entry;

      /* (attempt to) read the next entry from the source */
      SVN_ERR(read_l2p_entry_from_proto_index(file, &entry, &eof,
                                              scratch_pool));

      /* handle new revision */
      if (!eof && entry.item_index == item_index)
        {
          *offset = (apr_off_t)entry.offset - 1;
          *sub_item = entry.sub_item;
          break;
        }
    }

  SVN_ERR(svn_io_file_close(file, scratch_pool));

  return SVN_NO_ERROR;
}