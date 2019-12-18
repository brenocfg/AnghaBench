#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
struct TYPE_11__ {int ignore_unversioned; int found_mod; int /*<<< orphan*/  found_not_delete; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ modcheck_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_CEASE_INVOCATION ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  modcheck_callback ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_wc__db_has_db_mods (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__internal_walk_status (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__node_has_local_mods(svn_boolean_t *modified,
                            svn_boolean_t *all_edits_are_deletes,
                            svn_wc__db_t *db,
                            const char *local_abspath,
                            svn_boolean_t ignore_unversioned,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *scratch_pool)
{
  modcheck_baton_t modcheck_baton = { FALSE, FALSE, FALSE };
  svn_error_t *err;

  if (!all_edits_are_deletes)
    {
      SVN_ERR(svn_wc__db_has_db_mods(modified, db, local_abspath,
                                     scratch_pool));

      if (*modified)
        return SVN_NO_ERROR;
    }

  modcheck_baton.ignore_unversioned = ignore_unversioned;

  /* Walk the WC tree for status with depth infinity, looking for any local
   * modifications. If it's a "sparse" directory, that's OK: there can be
   * no local mods in the pieces that aren't present in the WC. */

  err = svn_wc__internal_walk_status(db, local_abspath,
                                     svn_depth_infinity,
                                     FALSE, FALSE, FALSE, NULL,
                                     modcheck_callback, &modcheck_baton,
                                     cancel_func, cancel_baton,
                                     scratch_pool);

  if (err && err->apr_err == SVN_ERR_CEASE_INVOCATION)
    svn_error_clear(err);
  else
    SVN_ERR(err);

  *modified = modcheck_baton.found_mod;
  if (all_edits_are_deletes)
    *all_edits_are_deletes = (modcheck_baton.found_mod
                              && !modcheck_baton.found_not_delete);

  return SVN_NO_ERROR;
}