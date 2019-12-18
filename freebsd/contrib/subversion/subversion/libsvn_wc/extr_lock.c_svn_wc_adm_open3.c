#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  db_provided; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_MISSING (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_LOCKED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* get_from_shared (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_all (TYPE_1__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_adm_open3(svn_wc_adm_access_t **adm_access,
                 svn_wc_adm_access_t *associated,
                 const char *path,
                 svn_boolean_t write_lock,
                 int levels_to_lock,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *pool)
{
  svn_wc__db_t *db;
  svn_boolean_t db_provided;

  /* Make sure that ASSOCIATED has a set of access batons, so that we can
     glom a reference to self into it. */
  if (associated)
    {
      const char *abspath;
      svn_wc_adm_access_t *lock;

      SVN_ERR(svn_dirent_get_absolute(&abspath, path, pool));
      lock = get_from_shared(abspath, associated->db, pool);
      if (lock && !IS_MISSING(lock))
        /* Already locked.  The reason we don't return the existing baton
           here is that the user is supposed to know whether a directory is
           locked: if it's not locked call svn_wc_adm_open, if it is locked
           call svn_wc_adm_retrieve.  */
        return svn_error_createf(SVN_ERR_WC_LOCKED, NULL,
                                 _("Working copy '%s' locked"),
                                 svn_dirent_local_style(path, pool));
      db = associated->db;
      db_provided = associated->db_provided;
    }
  else
    {
      /* Any baton creation is going to need a shared structure for holding
         data across the entire set. The caller isn't providing one, so we
         do it here.  */
      /* ### we could optimize around levels_to_lock==0, but much of this
         ### is going to be simplified soon anyways.  */
      SVN_ERR(svn_wc__db_open(&db, NULL /* ### config. need! */, FALSE, TRUE,
                              pool, pool));
      db_provided = FALSE;
    }

  return svn_error_trace(open_all(adm_access, path, db, db_provided,
                                  write_lock, levels_to_lock,
                                  cancel_func, cancel_baton, pool));
}