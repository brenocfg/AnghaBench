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
struct TYPE_2__ {scalar_t__ relpath; scalar_t__ commit_ctx; int /*<<< orphan*/  base_revision; } ;
typedef  TYPE_1__ proppatch_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_VERSION_NAME_HEADER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_set_lock_token_header (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
setup_proppatch_headers(serf_bucket_t *headers,
                        void *baton,
                        apr_pool_t *pool /* request pool */,
                        apr_pool_t *scratch_pool)
{
  proppatch_context_t *proppatch = baton;

  if (SVN_IS_VALID_REVNUM(proppatch->base_revision))
    {
      serf_bucket_headers_set(headers, SVN_DAV_VERSION_NAME_HEADER,
                              apr_psprintf(pool, "%ld",
                                           proppatch->base_revision));
    }

  if (proppatch->relpath && proppatch->commit_ctx)
    SVN_ERR(maybe_set_lock_token_header(headers, proppatch->commit_ctx,
                                        proppatch->relpath, pool));

  return SVN_NO_ERROR;
}