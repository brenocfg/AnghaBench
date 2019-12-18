#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_stream_close (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_open_readonly (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

__attribute__((used)) static const char *
systemd_release(apr_pool_t *pool)
{
  svn_error_t *err;
  svn_stream_t *stream;

  /* Open the file. */
  err = svn_stream_open_readonly(&stream, "/etc/os-release", pool, pool);
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      svn_error_clear(err);
      err = svn_stream_open_readonly(&stream, "/usr/lib/os-release", pool,
                                     pool);
    }
  if (err)
    {
      svn_error_clear(err);
      return NULL;
    }

  /* Look for the PRETTY_NAME line. */
  while (TRUE)
    {
      svn_stringbuf_t *line;
      svn_boolean_t eof;

      err = svn_stream_readline(stream, &line, "\n", &eof, pool);
      if (err)
        {
          svn_error_clear(err);
          return NULL;
        }

      if (!strncmp(line->data, "PRETTY_NAME=", 12))
        {
          svn_stringbuf_t *release_name;

          /* The value may or may not be enclosed by double quotes.  We don't
           * attempt to strip them. */
          release_name = svn_stringbuf_create(line->data + 12, pool);
          svn_error_clear(svn_stream_close(stream));
          svn_stringbuf_strip_whitespace(release_name);
          return release_name->data;
        }

      if (eof)
        break;
    }

  /* The file did not contain a PRETTY_NAME line. */
  svn_error_clear(svn_stream_close(stream));
  return NULL;
}