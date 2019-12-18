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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_ENTRY_EXISTS ; 
 scalar_t__ SVN_ERR_ENTRY_FORBIDDEN ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 scalar_t__ SVN_ERR_WC_FOUND_CONFLICT ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_path_check_valid (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_read_info (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_deleted 130 
#define  svn_wc__db_status_normal 129 
#define  svn_wc__db_status_not_present 128 
 scalar_t__ svn_wc_is_adm_dir (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_can_add_node(svn_node_kind_t *kind_p,
                   svn_boolean_t *db_row_exists_p,
                   svn_boolean_t *is_wc_root_p,
                   svn_wc__db_t *db,
                   const char *local_abspath,
                   const char *copyfrom_url,
                   svn_revnum_t copyfrom_rev,
                   apr_pool_t *scratch_pool)
{
  const char *base_name = svn_dirent_basename(local_abspath, scratch_pool);
  svn_boolean_t is_wc_root;
  svn_node_kind_t kind;
  svn_boolean_t is_special;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(!copyfrom_url || (svn_uri_is_canonical(copyfrom_url,
                                                        scratch_pool)
                                   && SVN_IS_VALID_REVNUM(copyfrom_rev)));

  /* Check that the proposed node has an acceptable name. */
  if (svn_wc_is_adm_dir(base_name, scratch_pool))
    return svn_error_createf
      (SVN_ERR_ENTRY_FORBIDDEN, NULL,
       _("Can't create an entry with a reserved name while trying to add '%s'"),
       svn_dirent_local_style(local_abspath, scratch_pool));

  SVN_ERR(svn_path_check_valid(local_abspath, scratch_pool));

  /* Make sure something's there; set KIND and *KIND_P. */
  SVN_ERR(svn_io_check_special_path(local_abspath, &kind, &is_special,
                                    scratch_pool));
  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                             _("'%s' not found"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (kind == svn_node_unknown)
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("Unsupported node kind for path '%s'"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));
  if (kind_p)
    *kind_p = kind;

  /* Determine whether a DB row for this node EXISTS, and whether it
     IS_WC_ROOT.  If it exists, check that it is in an acceptable state for
     adding the new node; if not, return an error. */
  {
    svn_wc__db_status_t status;
    svn_boolean_t conflicted;
    svn_boolean_t exists;
    svn_error_t *err
      = svn_wc__db_read_info(&status, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL,
                             &conflicted,
                             NULL, NULL, NULL, NULL, NULL, NULL,
                             db, local_abspath,
                             scratch_pool, scratch_pool);

    if (err)
      {
        if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
          return svn_error_trace(err);

        svn_error_clear(err);
        exists = FALSE;
        is_wc_root = FALSE;
      }
    else
      {
        is_wc_root = FALSE;
        exists = TRUE;

        /* Note that the node may be in conflict even if it does not
         * exist on disk (certain tree conflict scenarios). */
        if (conflicted)
          return svn_error_createf(SVN_ERR_WC_FOUND_CONFLICT, NULL,
                                   _("'%s' is an existing item in conflict; "
                                   "please mark the conflict as resolved "
                                   "before adding a new item here"),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));
        switch (status)
          {
            case svn_wc__db_status_not_present:
              break;
            case svn_wc__db_status_deleted:
              /* A working copy root should never have a WORKING_NODE */
              SVN_ERR_ASSERT(!is_wc_root);
              break;
            case svn_wc__db_status_normal:
              SVN_ERR(svn_wc__db_is_wcroot(&is_wc_root, db, local_abspath,
                                           scratch_pool));

              if (is_wc_root && copyfrom_url)
                {
                  /* Integrate a sub working copy in a parent working copy
                     (legacy behavior) */
                  break;
                }
              else if (is_wc_root && is_special)
                {
                  /* Adding a symlink to a working copy root.
                     (special_tests.py 23: externals as symlink targets) */
                  break;
                }
              /* else: Fall through in default error */

            default:
              return svn_error_createf(
                               SVN_ERR_ENTRY_EXISTS, NULL,
                               _("'%s' is already under version control"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
          }
      } /* err */

    if (db_row_exists_p)
      *db_row_exists_p = exists;
    if (is_wc_root_p)
      *is_wc_root_p = is_wc_root;
  }

  return SVN_NO_ERROR;
}