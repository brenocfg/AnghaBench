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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stream_read2 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
full_read_fallback(svn_stream_t *stream, char *buffer, apr_size_t *len)
{
  apr_size_t remaining = *len;
  while (remaining > 0)
    {
      apr_size_t length = remaining;
      SVN_ERR(svn_stream_read2(stream, buffer, &length));

      if (length == 0)
        {
          *len -= remaining;
          return SVN_NO_ERROR;
        }

      remaining -= length;
      buffer += length;
    }

  return SVN_NO_ERROR;
}