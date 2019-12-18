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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct svn_wc__db_info_t {char const* repos_relpath; char const* repos_root_url; char const* repos_uuid; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_repos_info (int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_repos_root_url_relpath(const char **repos_relpath,
                           const char **repos_root_url,
                           const char **repos_uuid,
                           const struct svn_wc__db_info_t *info,
                           const char *parent_repos_relpath,
                           const char *parent_repos_root_url,
                           const char *parent_repos_uuid,
                           svn_wc__db_t *db,
                           const char *local_abspath,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  if (info->repos_relpath && info->repos_root_url)
    {
      *repos_relpath = apr_pstrdup(result_pool, info->repos_relpath);
      *repos_root_url = apr_pstrdup(result_pool, info->repos_root_url);
      *repos_uuid = apr_pstrdup(result_pool, info->repos_uuid);
    }
  else if (parent_repos_relpath && parent_repos_root_url)
    {
      *repos_relpath = svn_relpath_join(parent_repos_relpath,
                                        svn_dirent_basename(local_abspath,
                                                            NULL),
                                        result_pool);
      *repos_root_url = apr_pstrdup(result_pool, parent_repos_root_url);
      *repos_uuid = apr_pstrdup(result_pool, parent_repos_uuid);
    }
  else
    {
      SVN_ERR(svn_wc__db_read_repos_info(NULL,
                                         repos_relpath, repos_root_url,
                                         repos_uuid,
                                         db, local_abspath,
                                         result_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}