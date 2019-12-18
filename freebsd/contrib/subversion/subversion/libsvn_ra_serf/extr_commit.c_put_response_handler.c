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
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_4__ {int /*<<< orphan*/  handler; TYPE_1__* file_ctx; } ;
typedef  TYPE_2__ put_response_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  remote_result_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_RESULT_FULLTEXT_MD5_HEADER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 char* serf_bucket_headers_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * serf_bucket_response_get_headers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__expect_empty_body (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
put_response_handler(serf_request_t *request,
                     serf_bucket_t *response,
                     void *baton,
                     apr_pool_t *scratch_pool)
{
  put_response_ctx_t *prc = baton;
  serf_bucket_t *hdrs;
  const char *val;

  hdrs = serf_bucket_response_get_headers(response);
  val = serf_bucket_headers_get(hdrs, SVN_DAV_RESULT_FULLTEXT_MD5_HEADER);
  SVN_ERR(svn_checksum_parse_hex(&prc->file_ctx->remote_result_checksum,
                                 svn_checksum_md5, val, prc->file_ctx->pool));

  return svn_error_trace(
           svn_ra_serf__expect_empty_body(request, response,
                                          prc->handler, scratch_pool));
}