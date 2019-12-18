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
struct TYPE_4__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_EXTERNAL_PROPERTIES ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_prop_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_sqlite__column_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_token_null (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_externals_gather_definitions(apr_hash_t **externals,
                                        apr_hash_t **depths,
                                        svn_wc__db_t *db,
                                        const char *local_abspath,
                                        apr_pool_t *result_pool,
                                        apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  svn_sqlite__stmt_t *stmt;
  const char *local_relpath;
  svn_boolean_t have_row;
  svn_error_t *err = NULL;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              local_abspath, scratch_pool, iterpool));
  VERIFY_USABLE_WCROOT(wcroot);

  *externals = apr_hash_make(result_pool);
  if (depths != NULL)
    *depths = apr_hash_make(result_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_EXTERNAL_PROPERTIES));

  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      apr_hash_t *node_props;
      const char *external_value;

      svn_pool_clear(iterpool);
      err = svn_sqlite__column_properties(&node_props, stmt, 0, iterpool,
                                          iterpool);

      if (err)
        break;

      external_value = svn_prop_get_value(node_props, SVN_PROP_EXTERNALS);

      if (external_value)
        {
          const char *node_abspath;
          const char *node_relpath = svn_sqlite__column_text(stmt, 1, NULL);

          node_abspath = svn_dirent_join(wcroot->abspath, node_relpath,
                                         result_pool);

          svn_hash_sets(*externals, node_abspath,
                        apr_pstrdup(result_pool, external_value));

          if (depths)
            {
              svn_depth_t depth
                = svn_sqlite__column_token_null(stmt, 2, depth_map,
                                                svn_depth_unknown);

              svn_hash_sets(*depths, node_abspath,
                            /* Use static string */
                            svn_token__to_word(depth_map, depth));
            }
        }

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  svn_pool_destroy(iterpool);

  return svn_error_trace(svn_error_compose_create(err,
                                                  svn_sqlite__reset(stmt)));
}