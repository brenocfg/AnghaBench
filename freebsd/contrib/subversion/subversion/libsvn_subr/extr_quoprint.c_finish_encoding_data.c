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
struct encode_baton {scalar_t__ linelen; int /*<<< orphan*/  pool; int /*<<< orphan*/  output; } ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_write (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static svn_error_t *
finish_encoding_data(void *baton)
{
  struct encode_baton *eb = baton;
  svn_error_t *err = SVN_NO_ERROR;
  apr_size_t len;

  /* Terminate the current output line if it's not empty.  */
  if (eb->linelen > 0)
    {
      len = 2;
      err = svn_stream_write(eb->output, "=\n", &len);
    }

  /* Pass on the close request and clean up the baton.  */
  if (err == SVN_NO_ERROR)
    err = svn_stream_close(eb->output);
  svn_pool_destroy(eb->pool);
  return err;
}