#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ blame_context_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TXDELTA ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
blame_cdata(svn_ra_serf__xml_estate_t *xes,
            void *baton,
            int current_state,
            const char *data,
            apr_size_t len,
            apr_pool_t *scratch_pool)
{
  blame_context_t *blame_ctx = baton;

  if (current_state == TXDELTA)
    {
      SVN_ERR(svn_stream_write(blame_ctx->stream, data, &len));
      /* Ignore the returned LEN value.  */
    }

  return SVN_NO_ERROR;
}