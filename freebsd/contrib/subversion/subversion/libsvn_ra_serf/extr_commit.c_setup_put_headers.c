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
struct TYPE_2__ {int /*<<< orphan*/  relpath; int /*<<< orphan*/  commit_ctx; scalar_t__ result_checksum; scalar_t__ base_checksum; int /*<<< orphan*/  base_revision; } ;
typedef  TYPE_1__ file_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_DAV_BASE_FULLTEXT_MD5_HEADER ; 
 int /*<<< orphan*/  SVN_DAV_RESULT_FULLTEXT_MD5_HEADER ; 
 int /*<<< orphan*/  SVN_DAV_VERSION_NAME_HEADER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_set_lock_token_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
setup_put_headers(serf_bucket_t *headers,
                  void *baton,
                  apr_pool_t *pool /* request pool */,
                  apr_pool_t *scratch_pool)
{
  file_context_t *ctx = baton;

  if (SVN_IS_VALID_REVNUM(ctx->base_revision))
    {
      serf_bucket_headers_set(headers, SVN_DAV_VERSION_NAME_HEADER,
                              apr_psprintf(pool, "%ld", ctx->base_revision));
    }

  if (ctx->base_checksum)
    {
      serf_bucket_headers_set(headers, SVN_DAV_BASE_FULLTEXT_MD5_HEADER,
                              ctx->base_checksum);
    }

  if (ctx->result_checksum)
    {
      serf_bucket_headers_set(headers, SVN_DAV_RESULT_FULLTEXT_MD5_HEADER,
                              ctx->result_checksum);
    }

  SVN_ERR(maybe_set_lock_token_header(headers, ctx->commit_ctx,
                                      ctx->relpath, pool));

  return APR_SUCCESS;
}