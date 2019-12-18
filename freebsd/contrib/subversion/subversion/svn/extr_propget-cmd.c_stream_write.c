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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_UNEXPECTED_EOF ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char const*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
stream_write(svn_stream_t *out,
             const char *data,
             apr_size_t len)
{
  apr_size_t write_len = len;

  /* We're gonna bail on an incomplete write here only because we know
     that this stream is really stdout, which should never be blocking
     on us. */
  SVN_ERR(svn_stream_write(out, data, &write_len));
  if (write_len != len)
    return svn_error_create(SVN_ERR_STREAM_UNEXPECTED_EOF, NULL,
                            _("Error writing to stream"));
  return SVN_NO_ERROR;
}