#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_4__ {TYPE_2__* commit_ctx; int /*<<< orphan*/  relpath; int /*<<< orphan*/  non_recursive_if; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ delete_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {scalar_t__ keep_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_OPTIONS_HEADER ; 
 int /*<<< orphan*/  SVN_DAV_OPTION_KEEP_LOCKS ; 
 int /*<<< orphan*/  SVN_DAV_VERSION_NAME_HEADER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_set_lock_token_header (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_if_header_recursive (scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
setup_delete_headers(serf_bucket_t *headers,
                     void *baton,
                     apr_pool_t *pool /* request pool */,
                     apr_pool_t *scratch_pool)
{
  delete_context_t *del = baton;
  svn_boolean_t added;

  serf_bucket_headers_set(headers, SVN_DAV_VERSION_NAME_HEADER,
                          apr_ltoa(pool, del->revision));

  if (! del->non_recursive_if)
    SVN_ERR(setup_if_header_recursive(&added, headers, del->commit_ctx,
                                      del->relpath, pool));
  else
    {
      SVN_ERR(maybe_set_lock_token_header(headers, del->commit_ctx,
                                          del->relpath, pool));
      added = TRUE;
    }

  if (added && del->commit_ctx->keep_locks)
    serf_bucket_headers_setn(headers, SVN_DAV_OPTIONS_HEADER,
                                      SVN_DAV_OPTION_KEEP_LOCKS);

  return SVN_NO_ERROR;
}