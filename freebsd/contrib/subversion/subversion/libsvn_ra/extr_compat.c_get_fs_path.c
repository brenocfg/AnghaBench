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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_fspath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_path_relative_to_root (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_fs_path(const char **fs_path_p,
            svn_ra_session_t *session,
            const char *rel_path,
            apr_pool_t *pool)
{
  const char *url, *fs_path;

  SVN_ERR(svn_ra_get_session_url(session, &url, pool));
  SVN_ERR(svn_ra_get_path_relative_to_root(session, &fs_path, url, pool));
  *fs_path_p = svn_fspath__canonicalize(svn_relpath_join(fs_path,
                                                         rel_path, pool),
                                        pool);
  return SVN_NO_ERROR;
}