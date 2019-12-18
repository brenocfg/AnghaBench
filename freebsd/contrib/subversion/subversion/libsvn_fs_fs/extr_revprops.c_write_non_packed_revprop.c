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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ flush_to_disk; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_revprops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_flush_to_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_non_packed_revprop(const char **final_path,
                         const char **tmp_path,
                         svn_fs_t *fs,
                         svn_revnum_t rev,
                         apr_hash_t *proplist,
                         apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  apr_file_t *file;
  svn_stream_t *stream;
  *final_path = svn_fs_fs__path_revprops(fs, rev, pool);

  /* ### do we have a directory sitting around already? we really shouldn't
     ### have to get the dirname here. */
  SVN_ERR(svn_io_open_unique_file3(&file, tmp_path,
                                   svn_dirent_dirname(*final_path, pool),
                                   svn_io_file_del_none, pool, pool));
  stream = svn_stream_from_aprfile2(file, TRUE, pool);
  SVN_ERR(svn_hash_write2(proplist, stream, SVN_HASH_TERMINATOR, pool));
  SVN_ERR(svn_stream_close(stream));

  /* Flush temporary file to disk and close it. */
  if (ffd->flush_to_disk)
    SVN_ERR(svn_io_file_flush_to_disk(file, pool));
  SVN_ERR(svn_io_file_close(file, pool));

  return SVN_NO_ERROR;
}