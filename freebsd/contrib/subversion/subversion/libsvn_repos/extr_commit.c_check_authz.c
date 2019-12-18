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
typedef  int svn_repos_authz_access_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/  authz_baton; int /*<<< orphan*/  (* authz_callback ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNREADABLE ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNWRITABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svn_authz_write ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
check_authz(struct edit_baton *editor_baton, const char *path,
            svn_fs_root_t *root, svn_repos_authz_access_t required,
            apr_pool_t *pool)
{
  if (editor_baton->authz_callback)
    {
      svn_boolean_t allowed;

      SVN_ERR(editor_baton->authz_callback(required, &allowed, root, path,
                                           editor_baton->authz_baton, pool));
      if (!allowed)
        return svn_error_create(required & svn_authz_write ?
                                SVN_ERR_AUTHZ_UNWRITABLE :
                                SVN_ERR_AUTHZ_UNREADABLE,
                                NULL, "Access denied");
    }

  return SVN_NO_ERROR;
}