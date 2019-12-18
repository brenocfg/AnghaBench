#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STMT_HAS_SWITCHED ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (char const**,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
has_switched_subtrees(svn_boolean_t *is_switched,
                      svn_wc__db_wcroot_t *wcroot,
                      const char *local_relpath,
                      const char *trail_url,
                      apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_int64_t repos_id;
  const char *repos_relpath;

  /* Optional argument handling for caller */
  if (!is_switched)
    return SVN_NO_ERROR;

  *is_switched = FALSE;

  SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, NULL,
                                            &repos_relpath, &repos_id,
                                            NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL, NULL,
                                            wcroot, local_relpath,
                                            scratch_pool, scratch_pool));

  /* First do the cheap check where we only need info on the origin itself */
  if (trail_url != NULL)
    {
      const char *repos_root_url;
      const char *url;
      apr_size_t len1, len2;

      /* If the trailing part of the URL of the working copy directory
         does not match the given trailing URL then the whole working
         copy is switched. */

      SVN_ERR(svn_wc__db_fetch_repos_info(&repos_root_url, NULL, wcroot,
                                          repos_id, scratch_pool));
      url = svn_path_url_add_component2(repos_root_url, repos_relpath,
                                        scratch_pool);

      len1 = strlen(trail_url);
      len2 = strlen(url);
      if ((len1 > len2) || strcmp(url + len2 - len1, trail_url))
        {
          *is_switched = TRUE;
          return SVN_NO_ERROR;
        }
    }

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_HAS_SWITCHED));
  SVN_ERR(svn_sqlite__bindf(stmt, "iss", wcroot->wc_id, local_relpath, repos_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (have_row)
    *is_switched = TRUE;
  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}