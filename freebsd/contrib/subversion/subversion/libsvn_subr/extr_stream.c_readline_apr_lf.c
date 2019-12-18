#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* data; int len; scalar_t__ blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__LINE_CHUNK_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_gets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_io_file_name_get (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_chop (TYPE_1__*,int) ; 
 TYPE_1__* svn_stringbuf_create_ensure (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
readline_apr_lf(apr_file_t *file,
                svn_stringbuf_t **stringbuf,
                svn_boolean_t *eof,
                apr_pool_t *pool)
{
  svn_stringbuf_t *buf;

  buf = svn_stringbuf_create_ensure(SVN__LINE_CHUNK_SIZE, pool);
  while (1)
  {
    apr_status_t status;

    status = apr_file_gets(buf->data + buf->len,
                           (int) (buf->blocksize - buf->len),
                           file);
    buf->len += strlen(buf->data + buf->len);

    if (APR_STATUS_IS_EOF(status))
      {
        /* apr_file_gets() keeps the newline; strip it if necessary. */
        if (buf->len > 0 && buf->data[buf->len - 1] == '\n')
          svn_stringbuf_chop(buf, 1);

        *eof = TRUE;
        *stringbuf = buf;
        return SVN_NO_ERROR;
      }
    else if (status != APR_SUCCESS)
      {
        const char *fname;
        svn_error_t *err = svn_io_file_name_get(&fname, file, pool);
        if (err)
          fname = NULL;
        svn_error_clear(err);

        if (fname)
          return svn_error_wrap_apr(status,
                                    _("Can't read a line from file '%s'"),
                                    svn_dirent_local_style(fname, pool));
        else
          return svn_error_wrap_apr(status,
                                    _("Can't read a line from stream"));
      }

    /* Do we have the EOL?  If yes, strip it and return. */
    if (buf->len > 0 && buf->data[buf->len - 1] == '\n')
      {
        svn_stringbuf_chop(buf, 1);
        *eof = FALSE;
        *stringbuf = buf;
        return SVN_NO_ERROR;
      }

    /* Otherwise, prepare to read the next chunk. */
    svn_stringbuf_ensure(buf, buf->blocksize + SVN__LINE_CHUNK_SIZE);
  }
}