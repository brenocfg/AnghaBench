#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_17__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_VERSION_FILE_FORMAT ; 
 int SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT ; 
 int SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* check_format (int) ; 
 TYPE_2__* check_format_file_buffer_numeric (scalar_t__,int,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 TYPE_2__* svn_cstring_atoi (int*,scalar_t__) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stringbuf_from_file2 (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_format(int *pformat,
            int *max_files_per_dir,
            svn_boolean_t *use_log_addressing,
            const char *path,
            apr_pool_t *pool)
{
  svn_error_t *err;
  svn_stream_t *stream;
  svn_stringbuf_t *content;
  svn_stringbuf_t *buf;
  svn_boolean_t eos = FALSE;

  err = svn_stringbuf_from_file2(&content, path, pool);
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      /* Treat an absent format file as format 1.  Do not try to
         create the format file on the fly, because the repository
         might be read-only for us, or this might be a read-only
         operation, and the spirit of FSFS is to make no changes
         whatseover in read-only operations.  See thread starting at
         http://subversion.tigris.org/servlets/ReadMsg?list=dev&msgNo=97600
         for more. */
      svn_error_clear(err);
      *pformat = 1;
      *max_files_per_dir = 0;
      *use_log_addressing = FALSE;

      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

  stream = svn_stream_from_stringbuf(content, pool);
  SVN_ERR(svn_stream_readline(stream, &buf, "\n", &eos, pool));
  if (buf->len == 0 && eos)
    {
      /* Return a more useful error message. */
      return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
                               _("Can't read first line of format file '%s'"),
                               svn_dirent_local_style(path, pool));
    }

  /* Check that the first line contains only digits. */
  SVN_ERR(check_format_file_buffer_numeric(buf->data, 0, path, pool));
  SVN_ERR(svn_cstring_atoi(pformat, buf->data));

  /* Check that we support this format at all */
  SVN_ERR(check_format(*pformat));

  /* Set the default values for anything that can be set via an option. */
  *max_files_per_dir = 0;
  *use_log_addressing = FALSE;

  /* Read any options. */
  while (!eos)
    {
      SVN_ERR(svn_stream_readline(stream, &buf, "\n", &eos, pool));
      if (buf->len == 0)
        break;

      if (*pformat >= SVN_FS_FS__MIN_LAYOUT_FORMAT_OPTION_FORMAT &&
          strncmp(buf->data, "layout ", 7) == 0)
        {
          if (strcmp(buf->data + 7, "linear") == 0)
            {
              *max_files_per_dir = 0;
              continue;
            }

          if (strncmp(buf->data + 7, "sharded ", 8) == 0)
            {
              /* Check that the argument is numeric. */
              SVN_ERR(check_format_file_buffer_numeric(buf->data, 15, path, pool));
              SVN_ERR(svn_cstring_atoi(max_files_per_dir, buf->data + 15));
              continue;
            }
        }

      if (*pformat >= SVN_FS_FS__MIN_LOG_ADDRESSING_FORMAT &&
          strncmp(buf->data, "addressing ", 11) == 0)
        {
          if (strcmp(buf->data + 11, "physical") == 0)
            {
              *use_log_addressing = FALSE;
              continue;
            }

          if (strcmp(buf->data + 11, "logical") == 0)
            {
              *use_log_addressing = TRUE;
              continue;
            }
        }

      return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
         _("'%s' contains invalid filesystem format option '%s'"),
         svn_dirent_local_style(path, pool), buf->data);
    }

  /* Non-sharded repositories never use logical addressing.
   * If the format file is inconsistent in that respect, something
   * probably went wrong.
   */
  if (*use_log_addressing && !*max_files_per_dir)
    return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
       _("'%s' specifies logical addressing for a non-sharded repository"),
       svn_dirent_local_style(path, pool));

  return SVN_NO_ERROR;
}