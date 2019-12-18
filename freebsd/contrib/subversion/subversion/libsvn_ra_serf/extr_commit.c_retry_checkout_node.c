#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  commit_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_APMOD_BAD_BASELINE ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__* checkout_node (char const**,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
retry_checkout_node(const char **working_url,
                    const commit_context_t *commit_ctx,
                    const char *node_url,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_error_t *err = SVN_NO_ERROR;
  int retry_count = 5; /* Magic, arbitrary number. */

  do
    {
      svn_error_clear(err);

      err = checkout_node(working_url, commit_ctx, node_url,
                          result_pool, scratch_pool);

      /* There's a small chance of a race condition here if Apache is
         experiencing heavy commit concurrency or if the network has
         long latency.  It's possible that the value of HEAD changed
         between the time we fetched the latest baseline and the time
         we try to CHECKOUT that baseline.  If that happens, Apache
         will throw us a BAD_BASELINE error (deltaV says you can only
         checkout the latest baseline).  We just ignore that specific
         error and retry a few times, asking for the latest baseline
         again. */
      if (err && (err->apr_err != SVN_ERR_APMOD_BAD_BASELINE))
        return svn_error_trace(err);
    }
  while (err && retry_count--);

  return svn_error_trace(err);
}