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
struct TYPE_9__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_10__ {int format; int /*<<< orphan*/  flush_to_disk; scalar_t__ use_log_addressing; scalar_t__ max_files_per_dir; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int SVN_FS_FS__FORMAT_NUMBER ; 
 int SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT ; 
 int SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 char* path_format (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_set_file_read_only (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char*) ; 
 TYPE_1__* svn_stringbuf_createf (int /*<<< orphan*/ *,char*,int) ; 

svn_error_t *
svn_fs_fs__write_format(svn_fs_t *fs,
                        svn_boolean_t overwrite,
                        apr_pool_t *pool)
{
  svn_stringbuf_t *sb;
  fs_fs_data_t *ffd = fs->fsap_data;
  const char *path = path_format(fs, pool);

  SVN_ERR_ASSERT(1 <= ffd->format
                 && ffd->format <= SVN_FS_FS__FORMAT_NUMBER);

  sb = svn_stringbuf_createf(pool, "%d\n", ffd->format);

  if (ffd->format >= SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT)
    {
      if (ffd->max_files_per_dir)
        svn_stringbuf_appendcstr(sb, apr_psprintf(pool, "layout sharded %d\n",
                                                  ffd->max_files_per_dir));
      else
        svn_stringbuf_appendcstr(sb, "layout linear\n");
    }

  if (ffd->format >= SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT)
    {
      if (ffd->use_log_addressing)
        svn_stringbuf_appendcstr(sb, "addressing logical\n");
      else
        svn_stringbuf_appendcstr(sb, "addressing physical\n");
    }

  /* svn_io_write_version_file() does a load of magic to allow it to
     replace version files that already exist.  We only need to do
     that when we're allowed to overwrite an existing file. */
  if (! overwrite)
    {
      /* Create the file */
      SVN_ERR(svn_io_file_create(path, sb->data, pool));
    }
  else
    {
      SVN_ERR(svn_io_write_atomic2(path, sb->data, sb->len,
                                   NULL /* copy_perms_path */,
                                   ffd->flush_to_disk, pool));
    }

  /* And set the perms to make it read only */
  return svn_io_set_file_read_only(path, FALSE, pool);
}