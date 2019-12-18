#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_9__ {int format; int /*<<< orphan*/  flush_to_disk; int /*<<< orphan*/  max_files_per_dir; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_10__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int SVN_FS_X__FORMAT_NUMBER ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_format (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_set_file_read_only (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_stringbuf_createf (int /*<<< orphan*/ *,char*,int) ; 

svn_error_t *
svn_fs_x__write_format(svn_fs_t *fs,
                       svn_boolean_t overwrite,
                       apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *sb;
  const char *path = svn_fs_x__path_format(fs, scratch_pool);
  svn_fs_x__data_t *ffd = fs->fsap_data;

  SVN_ERR_ASSERT(1 <= ffd->format && ffd->format <= SVN_FS_X__FORMAT_NUMBER);

  sb = svn_stringbuf_createf(scratch_pool, "%d\n", ffd->format);
  svn_stringbuf_appendcstr(sb, apr_psprintf(scratch_pool,
                                            "layout sharded %d\n",
                                            ffd->max_files_per_dir));

  /* svn_io_write_version_file() does a load of magic to allow it to
     replace version files that already exist.  We only need to do
     that when we're allowed to overwrite an existing file. */
  if (! overwrite)
    {
      /* Create the file */
      SVN_ERR(svn_io_file_create(path, sb->data, scratch_pool));
    }
  else
    {
      SVN_ERR(svn_io_write_atomic2(path, sb->data, sb->len,
                                   NULL /* copy_perms_path */,
                                   ffd->flush_to_disk, scratch_pool));
    }

  /* And set the perms to make it read only */
  return svn_io_set_file_read_only(path, FALSE, scratch_pool);
}