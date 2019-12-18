#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_7__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  block ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_FILENAME ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fileext_tolower (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_file_read (int /*<<< orphan*/ *,unsigned char*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_io_is_binary_data (unsigned char*,int) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_path_splitext (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_detect_mimetype2(const char **mimetype,
                        const char *file,
                        apr_hash_t *mimetype_map,
                        apr_pool_t *pool)
{
  static const char * const generic_binary = "application/octet-stream";

  svn_node_kind_t kind;
  apr_file_t *fh;
  svn_error_t *err;
  unsigned char block[1024];
  apr_size_t amt_read = sizeof(block);

  /* Default return value is NULL. */
  *mimetype = NULL;

  /* If there is a mimetype_map provided, we'll first try to look up
     our file's extension in the map.  Failing that, we'll run the
     heuristic. */
  if (mimetype_map)
    {
      const char *type_from_map;
      char *path_ext; /* Can point to physical const memory but only when
                         svn_path_splitext sets it to "". */
      svn_path_splitext(NULL, (const char **)&path_ext, file, pool);
      fileext_tolower(path_ext);
      if ((type_from_map = svn_hash_gets(mimetype_map, path_ext)))
        {
          *mimetype = type_from_map;
          return SVN_NO_ERROR;
        }
    }

  /* See if this file even exists, and make sure it really is a file. */
  SVN_ERR(svn_io_check_path(file, &kind, pool));
  if (kind != svn_node_file)
    return svn_error_createf(SVN_ERR_BAD_FILENAME, NULL,
                             _("Can't detect MIME type of non-file '%s'"),
                             svn_dirent_local_style(file, pool));

  SVN_ERR(svn_io_file_open(&fh, file, APR_READ, 0, pool));

  /* Read a block of data from FILE. */
  err = svn_io_file_read(fh, block, &amt_read, pool);
  if (err && ! APR_STATUS_IS_EOF(err->apr_err))
    return err;
  svn_error_clear(err);

  /* Now close the file.  No use keeping it open any more.  */
  SVN_ERR(svn_io_file_close(fh, pool));

  if (svn_io_is_binary_data(block, amt_read))
    *mimetype = generic_binary;

  return SVN_NO_ERROR;
}