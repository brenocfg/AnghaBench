#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_client_get_repos_root (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_uuid_from_url(const char **uuid,
                         const char *url,
                         svn_client_ctx_t *ctx,
                         apr_pool_t *pool)
{
  svn_error_t *err;
  apr_pool_t *subpool = svn_pool_create(pool);

  err = svn_client_get_repos_root(NULL, uuid, url,
                                  ctx, pool, subpool);
  /* destroy the RA session */
  svn_pool_destroy(subpool);

  return svn_error_trace(err);
}