#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  does_node_exist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  get_min_max_revisions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_db_mods (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* has_switched_subtrees (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_sparse_checkout_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
revision_status_txn(svn_revnum_t *min_revision,
                    svn_revnum_t *max_revision,
                    svn_boolean_t *is_sparse_checkout,
                    svn_boolean_t *is_modified,
                    svn_boolean_t *is_switched,
                    svn_wc__db_wcroot_t *wcroot,
                    const char *local_relpath,
                    svn_wc__db_t *db,
                    const char *trail_url,
                    svn_boolean_t committed,
                    apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_boolean_t exists;

  SVN_ERR(does_node_exist(&exists, wcroot, local_relpath));

  if (!exists)
    {
      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                               _("The node '%s' was not found."),
                               path_for_error_message(wcroot, local_relpath,
                                                      scratch_pool));
    }

  /* Determine mixed-revisionness. */
  SVN_ERR(get_min_max_revisions(min_revision, max_revision, wcroot,
                                local_relpath, committed, scratch_pool));

  /* Determine sparseness. */
  SVN_ERR(is_sparse_checkout_internal(is_sparse_checkout, wcroot,
                                      local_relpath, scratch_pool));

  /* Check for switched nodes. */
  {
    err = has_switched_subtrees(is_switched, wcroot, local_relpath,
                                trail_url, scratch_pool);

    if (err)
      {
        if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
          return svn_error_trace(err);

        svn_error_clear(err); /* No Base node, but no fatal error */
        *is_switched = FALSE;
      }
  }

  /* Check for db mods. */
  SVN_ERR(has_db_mods(is_modified, wcroot, local_relpath, scratch_pool));

  return SVN_NO_ERROR;
}