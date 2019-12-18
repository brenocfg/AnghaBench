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
typedef  int /*<<< orphan*/  svn_error_t ;
struct recover_read_from_file_baton {scalar_t__ remaining; int /*<<< orphan*/  stream; } ;
typedef  scalar_t__ apr_size_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_stream_read_full (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
read_handler_recover(void *baton, char *buffer, apr_size_t *len)
{
  struct recover_read_from_file_baton *b = baton;
  apr_size_t bytes_to_read = *len;

  if (b->remaining == 0)
    {
      /* Return a successful read of zero bytes to signal EOF. */
      *len = 0;
      return SVN_NO_ERROR;
    }

  if ((apr_int64_t)bytes_to_read > (apr_int64_t)b->remaining)
    bytes_to_read = (apr_size_t)b->remaining;
  b->remaining -= bytes_to_read;

  return svn_stream_read_full(b->stream, buffer, &bytes_to_read);
}