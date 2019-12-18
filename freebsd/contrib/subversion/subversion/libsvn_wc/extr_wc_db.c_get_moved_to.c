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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_moved_to(const char **moved_to_relpath_p,
             const char **moved_to_op_root_relpath_p,
             svn_boolean_t *scan,
             svn_sqlite__stmt_t *stmt,
             const char *current_relpath,
             svn_wc__db_wcroot_t *wcroot,
             const char *local_relpath,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  const char *moved_to_relpath = svn_sqlite__column_text(stmt, 3, NULL);

  if (moved_to_relpath)
    {
      const char *moved_to_op_root_relpath = moved_to_relpath;

      if (strcmp(current_relpath, local_relpath))
        {
          /* LOCAL_RELPATH is a child inside the move op-root. */
          const char *moved_child_relpath;

          /* The CURRENT_RELPATH is the op_root of the delete-half of
           * the move. LOCAL_RELPATH is a child that was moved along.
           * Compute the child's new location within the move target. */
          moved_child_relpath = svn_relpath_skip_ancestor(current_relpath,
                                                          local_relpath);
          SVN_ERR_ASSERT(moved_child_relpath &&
                         strlen(moved_child_relpath) > 0);
          moved_to_relpath = svn_relpath_join(moved_to_op_root_relpath,
                                              moved_child_relpath,
                                              result_pool);
        }

      if (moved_to_op_root_relpath && moved_to_op_root_relpath_p)
        *moved_to_op_root_relpath_p
          = apr_pstrdup(result_pool, moved_to_op_root_relpath);

      if (moved_to_relpath && moved_to_relpath_p)
        *moved_to_relpath_p
          = apr_pstrdup(result_pool, moved_to_relpath);

      *scan = FALSE;
    }

  return SVN_NO_ERROR;
}