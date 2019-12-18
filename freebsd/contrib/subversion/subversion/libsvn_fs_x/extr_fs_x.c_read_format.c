#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_VERSION_FILE_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_format (int) ; 
 int /*<<< orphan*/  check_format_file_buffer_numeric (scalar_t__,int,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  svn_cstring_atoi (int*,scalar_t__) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_format(int *pformat,
            int *max_files_per_dir,
            const char *path,
            apr_pool_t *scratch_pool)
{
  svn_stream_t *stream;
  svn_stringbuf_t *content;
  svn_stringbuf_t *buf;
  svn_boolean_t eos = FALSE;

  SVN_ERR(svn_stringbuf_from_file2(&content, path, scratch_pool));
  stream = svn_stream_from_stringbuf(content, scratch_pool);
  SVN_ERR(svn_stream_readline(stream, &buf, "\n", &eos, scratch_pool));
  if (buf->len == 0 && eos)
    {
      /* Return a more useful error message. */
      return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
                               _("Can't read first line of format file '%s'"),
                               svn_dirent_local_style(path, scratch_pool));
    }

  /* Check that the first line contains only digits. */
  SVN_ERR(check_format_file_buffer_numeric(buf->data, 0, path, scratch_pool));
  SVN_ERR(svn_cstring_atoi(pformat, buf->data));

  /* Check that we support this format at all */
  SVN_ERR(check_format(*pformat));

  /* Read any options. */
  SVN_ERR(svn_stream_readline(stream, &buf, "\n", &eos, scratch_pool));
  if (!eos && strncmp(buf->data, "layout sharded ", 15) == 0)
    {
      /* Check that the argument is numeric. */
      SVN_ERR(check_format_file_buffer_numeric(buf->data, 15, path,
                                               scratch_pool));
      SVN_ERR(svn_cstring_atoi(max_files_per_dir, buf->data + 15));
    }
  else
    return svn_error_createf(SVN_ERR_BAD_VERSION_FILE_FORMAT, NULL,
                  _("'%s' contains invalid filesystem format option '%s'"),
                  svn_dirent_local_style(path, scratch_pool), buf->data);

  return SVN_NO_ERROR;
}