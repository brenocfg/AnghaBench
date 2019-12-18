#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ repository_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_repos_relative_url (char const*) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_path_resolve_repos_relative_url (char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_get_file_url_from_dirent (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
canonicalize_access_file(const char **access_file, repository_t *repository,
                         const char *repos_root, apr_pool_t *pool)
{
  if (svn_path_is_url(*access_file))
    {
      *access_file = svn_uri_canonicalize(*access_file, pool);
    }
  else if (svn_path_is_repos_relative_url(*access_file))
    {
      const char *repos_root_url;

      SVN_ERR(svn_uri_get_file_url_from_dirent(&repos_root_url, repos_root,
                                               pool));
      SVN_ERR(svn_path_resolve_repos_relative_url(access_file, *access_file,
                                                  repos_root_url, pool));
      *access_file = svn_uri_canonicalize(*access_file, pool);
    }
  else
    {
      *access_file = svn_dirent_internal_style(*access_file, pool);
      *access_file = svn_dirent_join(repository->base, *access_file, pool);
    }

  return SVN_NO_ERROR;
}