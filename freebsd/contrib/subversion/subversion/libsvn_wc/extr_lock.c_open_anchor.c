#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EACCES (scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ IS_MISSING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_LOCKED ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* adm_available (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* child_is_disjoint (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* close_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* open_all (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* open_single (int /*<<< orphan*/ **,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 TYPE_1__* svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_clear_access (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_temp_get_access (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_adm_close2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_anchor(svn_wc_adm_access_t **anchor_access,
            svn_wc_adm_access_t **target_access,
            const char **target,
            svn_wc__db_t *db,
            svn_boolean_t db_provided,
            const char *path,
            svn_boolean_t write_lock,
            int levels_to_lock,
            svn_cancel_func_t cancel_func,
            void *cancel_baton,
            apr_pool_t *pool)
{
  const char *base_name = svn_dirent_basename(path, pool);

  /* Any baton creation is going to need a shared structure for holding
     data across the entire set. The caller isn't providing one, so we
     do it here.  */
  /* ### we could maybe skip the shared struct for levels_to_lock==0, but
     ### given that we need DB for format detection, may as well keep this.
     ### in any case, much of this is going to be simplified soon anyways.  */
  if (!db_provided)
    SVN_ERR(svn_wc__db_open(&db, NULL, /* ### config. need! */ FALSE, TRUE,
                            pool, pool));

  if (svn_path_is_empty(path)
      || svn_dirent_is_root(path, strlen(path))
      || ! strcmp(base_name, ".."))
    {
      SVN_ERR(open_all(anchor_access, path, db, db_provided,
                       write_lock, levels_to_lock,
                       cancel_func, cancel_baton, pool));
      *target_access = *anchor_access;
      *target = "";
    }
  else
    {
      svn_error_t *err;
      svn_wc_adm_access_t *p_access = NULL;
      svn_wc_adm_access_t *t_access = NULL;
      const char *parent = svn_dirent_dirname(path, pool);
      const char *local_abspath;
      svn_error_t *p_access_err = SVN_NO_ERROR;

      SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

      /* Try to open parent of PATH to setup P_ACCESS */
      err = open_single(&p_access, parent, write_lock, db, db_provided,
                        pool, pool);
      if (err)
        {
          const char *abspath = svn_dirent_dirname(local_abspath, pool);
          svn_wc_adm_access_t *existing_adm = svn_wc__db_temp_get_access(db, abspath, pool);

          if (IS_MISSING(existing_adm))
            svn_wc__db_temp_clear_access(db, abspath, pool);
          else
            SVN_ERR_ASSERT(existing_adm == NULL);

          if (err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY)
            {
              svn_error_clear(err);
              p_access = NULL;
            }
          else if (write_lock && (err->apr_err == SVN_ERR_WC_LOCKED
                                  || APR_STATUS_IS_EACCES(err->apr_err)))
            {
              /* If P_ACCESS isn't to be returned then a read-only baton
                 will do for now, but keep the error in case we need it. */
              svn_error_t *err2 = open_single(&p_access, parent, FALSE,
                                              db, db_provided, pool, pool);
              if (err2)
                {
                  svn_error_clear(err2);
                  return err;
                }
              p_access_err = err;
            }
          else
            return err;
        }

      /* Try to open PATH to setup T_ACCESS */
      err = open_all(&t_access, path, db, db_provided, write_lock,
                     levels_to_lock, cancel_func, cancel_baton, pool);
      if (err)
        {
          if (p_access == NULL)
            {
              /* Couldn't open the parent or the target. Bail out.  */
              svn_error_clear(p_access_err);
              return svn_error_trace(err);
            }

          if (err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
            {
              if (p_access)
                svn_error_clear(svn_wc_adm_close2(p_access, pool));
              svn_error_clear(p_access_err);
              return svn_error_trace(err);
            }

          /* This directory is not under version control. Ignore it.  */
          svn_error_clear(err);
          t_access = NULL;
        }

      /* At this stage might have P_ACCESS, T_ACCESS or both */

      /* Check for switched or disjoint P_ACCESS and T_ACCESS */
      if (p_access && t_access)
        {
          svn_boolean_t disjoint;

          err = child_is_disjoint(&disjoint, db, local_abspath, pool);
          if (err)
            {
              svn_error_clear(p_access_err);
              svn_error_clear(svn_wc_adm_close2(p_access, pool));
              svn_error_clear(svn_wc_adm_close2(t_access, pool));
              return svn_error_trace(err);
            }

          if (disjoint)
            {
              /* Switched or disjoint, so drop P_ACCESS. Don't close any
                 descendants, or we might blast the child.  */
              err = close_single(p_access, FALSE /* preserve_lock */, pool);
              if (err)
                {
                  svn_error_clear(p_access_err);
                  svn_error_clear(svn_wc_adm_close2(t_access, pool));
                  return svn_error_trace(err);
                }
              p_access = NULL;
            }
        }

      /* We have a parent baton *and* we have an error related to opening
         the baton. That means we have a readonly baton, but that isn't
         going to work for us. (p_access would have been set to NULL if
         a writable parent baton is not required)  */
      if (p_access && p_access_err)
        {
          if (t_access)
            svn_error_clear(svn_wc_adm_close2(t_access, pool));
          svn_error_clear(svn_wc_adm_close2(p_access, pool));
          return svn_error_trace(p_access_err);
        }
      svn_error_clear(p_access_err);

      if (! t_access)
        {
          svn_boolean_t available;
          svn_node_kind_t kind;

          err = adm_available(&available, &kind, db, local_abspath, pool);

          if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
            svn_error_clear(err);
          else if (err)
            {
              svn_error_clear(svn_wc_adm_close2(p_access, pool));
              return svn_error_trace(err);
            }
        }

      *anchor_access = p_access ? p_access : t_access;
      *target_access = t_access ? t_access : p_access;

      if (! p_access)
        *target = "";
      else
        *target = base_name;
    }

  return SVN_NO_ERROR;
}