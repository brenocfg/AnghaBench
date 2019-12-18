#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  block_size; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auto_open (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_aligned_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__rev_file_seek(svn_fs_x__revision_file_t *file,
                        apr_off_t *buffer_start,
                        apr_off_t offset)
{
  SVN_ERR(auto_open(file));
  return svn_error_trace(svn_io_file_aligned_seek(file->file,
                                                  file->block_size,
                                                  buffer_start, offset,
                                                  file->pool));
}