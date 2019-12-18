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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client__parse_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__record_wc_mergeinfo (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mergeinfo_merge2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
extend_wc_mergeinfo(const char *target_abspath,
                    apr_hash_t *mergeinfo,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *pool)
{
  apr_hash_t *wc_mergeinfo;

  /* Get a fresh copy of the pre-existing state of the WC's mergeinfo
     updating it. */
  SVN_ERR(svn_client__parse_mergeinfo(&wc_mergeinfo, ctx->wc_ctx,
                                      target_abspath, pool, pool));

  /* Combine the provided mergeinfo with any mergeinfo from the WC. */
  if (wc_mergeinfo && mergeinfo)
    SVN_ERR(svn_mergeinfo_merge2(wc_mergeinfo, mergeinfo, pool, pool));
  else if (! wc_mergeinfo)
    wc_mergeinfo = mergeinfo;

  return svn_error_trace(
    svn_client__record_wc_mergeinfo(target_abspath, wc_mergeinfo,
                                    FALSE, ctx, pool));
}