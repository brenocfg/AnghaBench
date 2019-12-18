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
struct TYPE_4__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  db_provided; int /*<<< orphan*/  abspath; scalar_t__ closed; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__adm_area_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_close_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_temp_get_all_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_owns_lock (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_wclock_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_single(svn_wc_adm_access_t *adm_access,
             svn_boolean_t preserve_lock,
             apr_pool_t *scratch_pool)
{
  svn_boolean_t locked;

  if (adm_access->closed)
    return SVN_NO_ERROR;

  /* Physically unlock if required */
  SVN_ERR(svn_wc__db_wclock_owns_lock(&locked, adm_access->db,
                                      adm_access->abspath, TRUE,
                                      scratch_pool));
  if (locked)
    {
      if (!preserve_lock)
        {
          /* Remove the physical lock in the admin directory for
             PATH. It is acceptable for the administrative area to
             have disappeared, such as when the directory is removed
             from the working copy.  It is an error for the lock to
             have disappeared if the administrative area still exists. */

          svn_error_t *err = svn_wc__db_wclock_release(adm_access->db,
                                                       adm_access->abspath,
                                                       scratch_pool);
          if (err)
            {
              if (svn_wc__adm_area_exists(adm_access->abspath, scratch_pool))
                return err;
              svn_error_clear(err);
            }
        }
    }

  /* Reset to prevent further use of the lock. */
  adm_access->closed = TRUE;

  /* Detach from set */
  SVN_ERR(svn_wc__db_temp_close_access(adm_access->db, adm_access->abspath,
                                       adm_access, scratch_pool));

  /* Possibly close the underlying wc_db. */
  if (!adm_access->db_provided)
    {
      apr_hash_t *opened = svn_wc__db_temp_get_all_access(adm_access->db,
                                                          scratch_pool);
      if (apr_hash_count(opened) == 0)
        {
          SVN_ERR(svn_wc__db_close(adm_access->db));
          adm_access->db = NULL;
        }
    }

  return SVN_NO_ERROR;
}