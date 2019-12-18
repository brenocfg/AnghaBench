#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p2l_stream; int /*<<< orphan*/  pool; scalar_t__ block_size; TYPE_1__ p2l_info; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_x__packed_number_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_X__P2L_STREAM_PREFIX ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  auto_read_footer (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_x__packed_stream_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__rev_file_p2l_index(svn_fs_x__packed_number_stream_t **stream,
                             svn_fs_x__revision_file_t *file)
{
  if (file->p2l_stream== NULL)
    {
      SVN_ERR(auto_read_footer(file));
      SVN_ERR(svn_fs_x__packed_stream_open(&file->p2l_stream,
                                           file->file,
                                           file->p2l_info.start,
                                           file->p2l_info.end,
                                           SVN_FS_X__P2L_STREAM_PREFIX,
                                           (apr_size_t)file->block_size,
                                           file->pool,
                                           file->pool));
    }

  *stream = file->p2l_stream;
  return SVN_NO_ERROR;
}