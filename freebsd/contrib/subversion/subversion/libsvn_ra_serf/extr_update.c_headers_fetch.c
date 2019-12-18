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
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_3__ {char* delta_base; TYPE_2__* session; } ;
typedef  TYPE_1__ fetch_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ using_compression; } ;

/* Variables and functions */
 char* SVN_DAV_DELTA_BASE_HEADER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  svn_ra_serf__setup_svndiff_accept_encoding (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ svn_tristate_false ; 

__attribute__((used)) static svn_error_t *
headers_fetch(serf_bucket_t *headers,
              void *baton,
              apr_pool_t *pool /* request pool */,
              apr_pool_t *scratch_pool)
{
  fetch_ctx_t *fetch_ctx = baton;

  /* note that we have old VC URL */
  if (fetch_ctx->delta_base)
    {
      serf_bucket_headers_setn(headers, SVN_DAV_DELTA_BASE_HEADER,
                               fetch_ctx->delta_base);
      svn_ra_serf__setup_svndiff_accept_encoding(headers, fetch_ctx->session);
    }
  else if (fetch_ctx->session->using_compression != svn_tristate_false)
    {
      serf_bucket_headers_setn(headers, "Accept-Encoding", "gzip");
    }

  return SVN_NO_ERROR;
}