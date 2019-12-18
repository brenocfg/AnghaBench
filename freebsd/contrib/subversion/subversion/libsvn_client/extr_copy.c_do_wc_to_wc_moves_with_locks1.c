#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__copy_pair_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_wc_to_wc_moves_with_locks2 (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_wc_to_wc_moves_with_locks1(svn_client__copy_pair_t *pair,
                              const char *dst_parent_abspath,
                              svn_boolean_t lock_src,
                              svn_boolean_t lock_dst,
                              svn_boolean_t allow_mixed_revisions,
                              svn_boolean_t metadata_only,
                              svn_client_ctx_t *ctx,
                              apr_pool_t *scratch_pool)
{
  if (lock_dst)
    SVN_WC__CALL_WITH_WRITE_LOCK(
      do_wc_to_wc_moves_with_locks2(pair, dst_parent_abspath, lock_src,
                                    lock_dst, allow_mixed_revisions,
                                    metadata_only,
                                    ctx, scratch_pool),
      ctx->wc_ctx, dst_parent_abspath, FALSE, scratch_pool);
  else
    SVN_ERR(do_wc_to_wc_moves_with_locks2(pair, dst_parent_abspath, lock_src,
                                          lock_dst, allow_mixed_revisions,
                                          metadata_only,
                                          ctx, scratch_pool));

  return SVN_NO_ERROR;
}