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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  flush_to_disk; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_6__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 size_t svn__i64toa (char*,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_min_unpacked_rev (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,char*,size_t,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__write_min_unpacked_rev(svn_fs_t *fs,
                                 svn_revnum_t revnum,
                                 apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  const char *final_path;
  char buf[SVN_INT64_BUFFER_SIZE];
  apr_size_t len = svn__i64toa(buf, revnum);
  buf[len] = '\n';

  final_path = svn_fs_x__path_min_unpacked_rev(fs, scratch_pool);

  SVN_ERR(svn_io_write_atomic2(final_path, buf, len + 1,
                               final_path /* copy_perms */,
                               ffd->flush_to_disk, scratch_pool));

  return SVN_NO_ERROR;
}