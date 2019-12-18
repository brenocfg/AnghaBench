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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  full; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_authz_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_authz__parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_authz_parse(svn_authz_t **authz_p, svn_stream_t *stream,
                      svn_stream_t *groups_stream, apr_pool_t *pool)
{
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  svn_authz_t *authz = apr_pcalloc(pool, sizeof(*authz));
  authz->pool = pool;

  /* Parse the configuration and construct the full authz model from it. */
  SVN_ERR(svn_authz__parse(&authz->full, stream, groups_stream, pool,
                           scratch_pool));

  svn_pool_destroy(scratch_pool);

  *authz_p = authz;
  return SVN_NO_ERROR;
}