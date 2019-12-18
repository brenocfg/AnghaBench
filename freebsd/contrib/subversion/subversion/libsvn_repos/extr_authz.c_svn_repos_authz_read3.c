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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  authz_id; int /*<<< orphan*/  full; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_authz_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  authz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_authz_read3(svn_authz_t **authz_p,
                      const char *path,
                      const char *groups_path,
                      svn_boolean_t must_exist,
                      svn_repos_t *repos_hint,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_authz_t *authz = apr_pcalloc(result_pool, sizeof(*authz));
  authz->pool = result_pool;

  SVN_ERR(authz_read(&authz->full, &authz->authz_id, path, groups_path,
                     must_exist, repos_hint, result_pool, scratch_pool));

  *authz_p = authz;
  return SVN_NO_ERROR;
}