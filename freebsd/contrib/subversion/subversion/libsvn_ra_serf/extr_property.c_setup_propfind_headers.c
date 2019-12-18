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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_2__ {scalar_t__ label; scalar_t__ depth; } ;
typedef  TYPE_1__ propfind_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
setup_propfind_headers(serf_bucket_t *headers,
                       void *setup_baton,
                       apr_pool_t *pool /* request pool */,
                       apr_pool_t *scratch_pool)
{
  propfind_context_t *ctx = setup_baton;

  serf_bucket_headers_setn(headers, "Depth", ctx->depth);
  if (ctx->label)
    {
      serf_bucket_headers_setn(headers, "Label", ctx->label);
    }

  return SVN_NO_ERROR;
}