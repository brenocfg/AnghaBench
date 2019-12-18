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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  prune_deleted (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_access_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_access_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_access_pool_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_access_set_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__entries_read_internal(apr_hash_t **entries,
                              svn_wc_adm_access_t *adm_access,
                              svn_boolean_t show_hidden,
                              apr_pool_t *pool)
{
  apr_hash_t *new_entries;

  new_entries = svn_wc__adm_access_entries(adm_access);
  if (! new_entries)
    {
      svn_wc__db_t *db = svn_wc__adm_get_db(adm_access);
      const char *local_abspath = svn_wc__adm_access_abspath(adm_access);
      apr_pool_t *result_pool = svn_wc__adm_access_pool_internal(adm_access);

      SVN_ERR(read_entries(&new_entries, db, local_abspath,
                           result_pool, pool));

      svn_wc__adm_access_set_entries(adm_access, new_entries);
    }

  if (show_hidden)
    *entries = new_entries;
  else
    SVN_ERR(prune_deleted(entries, new_entries,
                          svn_wc__adm_access_pool_internal(adm_access),
                          pool));

  return SVN_NO_ERROR;
}