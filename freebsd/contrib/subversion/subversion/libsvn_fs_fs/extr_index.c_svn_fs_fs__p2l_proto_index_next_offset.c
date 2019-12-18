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
struct TYPE_3__ {scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_1__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  APR_SET ; 
 scalar_t__ P2L_PROTO_INDEX_ENTRY_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_p2l_entry_from_proto_index (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__p2l_proto_index_next_offset(apr_off_t *next_offset,
                                       apr_file_t *proto_index,
                                       apr_pool_t *scratch_pool)
{
  apr_off_t offset = 0;

  /* Empty index file? */
  SVN_ERR(svn_io_file_seek(proto_index, APR_END, &offset, scratch_pool));
  if (offset == 0)
    {
      *next_offset = 0;
    }
  else
    {
      /* At least one entry.  Read last entry. */
      svn_fs_fs__p2l_entry_t entry;
      offset -= P2L_PROTO_INDEX_ENTRY_SIZE;

      SVN_ERR(svn_io_file_seek(proto_index, APR_SET, &offset, scratch_pool));
      SVN_ERR(read_p2l_entry_from_proto_index(proto_index, &entry,
                                              NULL, scratch_pool));

      /* Return next offset. */
      *next_offset = entry.offset + entry.size;
    }

  return SVN_NO_ERROR;
}