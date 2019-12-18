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
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ format; int /*<<< orphan*/  flush_to_disk; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 
 char* svn_fs_fs__path_current (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__write_current(svn_fs_t *fs,
                         svn_revnum_t rev,
                         apr_uint64_t next_node_id,
                         apr_uint64_t next_copy_id,
                         apr_pool_t *pool)
{
  char *buf;
  const char *name;
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Now we can just write out this line. */
  if (ffd->format >= SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT)
    {
      buf = apr_psprintf(pool, "%ld\n", rev);
    }
  else
    {
      char node_id_str[SVN_INT64_BUFFER_SIZE];
      char copy_id_str[SVN_INT64_BUFFER_SIZE];
      svn__ui64tobase36(node_id_str, next_node_id);
      svn__ui64tobase36(copy_id_str, next_copy_id);

      buf = apr_psprintf(pool, "%ld %s %s\n", rev, node_id_str, copy_id_str);
    }

  name = svn_fs_fs__path_current(fs, pool);
  SVN_ERR(svn_io_write_atomic2(name, buf, strlen(buf),
                               name /* copy_perms_path */,
                               ffd->flush_to_disk, pool));

  return SVN_NO_ERROR;
}