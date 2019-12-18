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
struct TYPE_2__ {int /*<<< orphan*/  revision; scalar_t__ force; } ;
typedef  TYPE_1__ lock_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_DAV_OPTIONS_HEADER ; 
 int /*<<< orphan*/  SVN_DAV_OPTION_LOCK_STEAL ; 
 int /*<<< orphan*/  SVN_DAV_VERSION_NAME_HEADER ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
set_lock_headers(serf_bucket_t *headers,
                 void *baton,
                 apr_pool_t *pool /* request pool */,
                 apr_pool_t *scratch_pool)
{
  lock_ctx_t *lock_ctx = baton;

  if (lock_ctx->force)
    {
      serf_bucket_headers_set(headers, SVN_DAV_OPTIONS_HEADER,
                              SVN_DAV_OPTION_LOCK_STEAL);
    }

  if (SVN_IS_VALID_REVNUM(lock_ctx->revision))
    {
      serf_bucket_headers_set(headers, SVN_DAV_VERSION_NAME_HEADER,
                              apr_ltoa(pool, lock_ctx->revision));
    }

  return APR_SUCCESS;
}