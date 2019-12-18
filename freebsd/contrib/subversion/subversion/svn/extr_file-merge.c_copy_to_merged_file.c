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
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SIZE_MAX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IO_WRITE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ *,TYPE_1__**,char const**,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char const*) ; 

__attribute__((used)) static svn_error_t *
copy_to_merged_file(svn_linenum_t *new_current_line,
                    apr_file_t *merged_file,
                    apr_file_t *source_file,
                    apr_off_t start,
                    apr_off_t len,
                    svn_linenum_t current_line,
                    apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  svn_stringbuf_t *line;
  apr_size_t lines_read;
  apr_size_t lines_copied;
  svn_boolean_t eof;
  svn_linenum_t orig_current_line = current_line;

  lines_read = 0;
  iterpool = svn_pool_create(scratch_pool);
  while (current_line < start)
    {
      svn_pool_clear(iterpool);

      SVN_ERR(svn_io_file_readline(source_file, &line, NULL, &eof,
                                   APR_SIZE_MAX, iterpool, iterpool));
      if (eof)
        break;

      current_line++;
      lines_read++;
    }

  lines_copied = 0;
  while (lines_copied < len)
    {
      apr_size_t bytes_written;
      const char *eol_str;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_io_file_readline(source_file, &line, &eol_str, &eof,
                                   APR_SIZE_MAX, iterpool, iterpool));
      if (eol_str)
        svn_stringbuf_appendcstr(line, eol_str);
      SVN_ERR(svn_io_file_write_full(merged_file, line->data, line->len,
                                     &bytes_written, iterpool));
      if (bytes_written != line->len)
        return svn_error_create(SVN_ERR_IO_WRITE_ERROR, NULL,
                                _("Could not write data to merged file"));
      if (eof)
        break;
      lines_copied++;
    }
  svn_pool_destroy(iterpool);

  *new_current_line = orig_current_line + lines_read + lines_copied;

  return SVN_NO_ERROR;
}