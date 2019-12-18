#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {TYPE_1__* session; } ;
typedef  TYPE_2__ stream_ctx_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ using_compression; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ svn_tristate_false ; 

__attribute__((used)) static svn_error_t *
headers_fetch(serf_bucket_t *headers,
              void *baton,
              apr_pool_t *pool /* request pool */,
              apr_pool_t *scratch_pool)
{
  stream_ctx_t *fetch_ctx = baton;

  if (fetch_ctx->session->using_compression != svn_tristate_false)
    {
      serf_bucket_headers_setn(headers, "Accept-Encoding", "gzip");
    }

  return SVN_NO_ERROR;
}