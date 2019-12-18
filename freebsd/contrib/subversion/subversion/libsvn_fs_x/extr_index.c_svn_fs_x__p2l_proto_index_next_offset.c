#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_off_t_from_proto_index (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__p2l_proto_index_next_offset(apr_off_t *next_offset,
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
      /* The last 64 bits contain the value we are looking for. */
      offset -= sizeof(apr_uint64_t);
      SVN_ERR(svn_io_file_seek(proto_index, APR_SET, &offset, scratch_pool));
      SVN_ERR(read_off_t_from_proto_index(proto_index, next_offset, NULL,
                                          scratch_pool));
    }

  return SVN_NO_ERROR;
}