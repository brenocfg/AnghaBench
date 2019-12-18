#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stream_malformed () ; 
 int /*<<< orphan*/  stream_ran_dry () ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static svn_error_t *
read_key_or_val(char **pbuf,
                svn_filesize_t *actual_length,
                svn_stream_t *stream,
                apr_size_t len,
                apr_pool_t *pool)
{
  char *buf = apr_pcalloc(pool, len + 1);
  apr_size_t numread;
  char c;

  numread = len;
  SVN_ERR(svn_stream_read_full(stream, buf, &numread));
  *actual_length += numread;
  if (numread != len)
    return svn_error_trace(stream_ran_dry());
  buf[len] = '\0';

  /* Suck up extra newline after key data */
  numread = 1;
  SVN_ERR(svn_stream_read_full(stream, &c, &numread));
  *actual_length += numread;
  if (numread != 1)
    return svn_error_trace(stream_ran_dry());
  if (c != '\n')
    return svn_error_trace(stream_malformed());

  *pbuf = buf;
  return SVN_NO_ERROR;
}