#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_repos_authz_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; TYPE_3__* client_info; TYPE_2__* repository; } ;
typedef  TYPE_1__ server_baton_t ;
struct TYPE_7__ {scalar_t__ username_case; int /*<<< orphan*/  authz_repos_name; int /*<<< orphan*/  authzdb; } ;
typedef  TYPE_2__ repository_t ;
struct TYPE_8__ {char* authz_user; scalar_t__ user; } ;
typedef  TYPE_3__ client_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ CASE_FORCE_LOWER ; 
 scalar_t__ CASE_FORCE_UPPER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  convert_case (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_authz_denied (char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_authz_check_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *authz_check_access(svn_boolean_t *allowed,
                                       const char *path,
                                       svn_repos_authz_access_t required,
                                       server_baton_t *b,
                                       apr_pool_t *pool)
{
  repository_t *repository = b->repository;
  client_info_t *client_info = b->client_info;

  /* If authz cannot be performed, grant access.  This is NOT the same
     as the default policy when authz is performed on a path with no
     rules.  In the latter case, the default is to deny access, and is
     set by svn_repos_authz_check_access. */
  if (!repository->authzdb)
    {
      *allowed = TRUE;
      return SVN_NO_ERROR;
    }

  /* If the authz request is for the empty path (ie. ""), replace it
     with the root path.  This happens because of stripping done at
     various levels in svnserve that remove the leading / on an
     absolute path. Passing such a malformed path to the authz
     routines throws them into an infinite loop and makes them miss
     ACLs. */
  if (path && *path != '/')
    path = svn_fspath__canonicalize(path, pool);

  /* If we have a username, and we've not yet used it + any username
     case normalization that might be requested to determine "the
     username we used for authz purposes", do so now. */
  if (client_info->user && (! client_info->authz_user))
    {
      char *authz_user = apr_pstrdup(b->pool, client_info->user);
      if (repository->username_case == CASE_FORCE_UPPER)
        convert_case(authz_user, TRUE);
      else if (repository->username_case == CASE_FORCE_LOWER)
        convert_case(authz_user, FALSE);

      client_info->authz_user = authz_user;
    }

  SVN_ERR(svn_repos_authz_check_access(repository->authzdb,
                                       repository->authz_repos_name,
                                       path, client_info->authz_user,
                                       required, allowed, pool));
  if (!*allowed)
    SVN_ERR(log_authz_denied(path, required, b, pool));

  return SVN_NO_ERROR;
}