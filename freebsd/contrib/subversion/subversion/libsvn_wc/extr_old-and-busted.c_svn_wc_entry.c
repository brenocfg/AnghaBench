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
typedef  int /*<<< orphan*/  svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__entries_read_internal (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__entry_is_hidden (scalar_t__*,int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_wc_entry(const svn_wc_entry_t **entry,
             const char *path,
             svn_wc_adm_access_t *adm_access,
             svn_boolean_t show_hidden,
             apr_pool_t *pool)
{
  svn_wc__db_t *db = svn_wc__adm_get_db(adm_access);
  const char *local_abspath;
  svn_wc_adm_access_t *dir_access;
  const char *entry_name;
  apr_hash_t *entries;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));

  /* Does the provided path refer to a directory with an associated
     access baton?  */
  dir_access = svn_wc__adm_retrieve_internal2(db, local_abspath, pool);
  if (dir_access == NULL)
    {
      /* Damn. Okay. Assume the path is to a child, and let's look for
         a baton associated with its parent.  */

      const char *dir_abspath;

      svn_dirent_split(&dir_abspath, &entry_name, local_abspath, pool);

      dir_access = svn_wc__adm_retrieve_internal2(db, dir_abspath, pool);
    }
  else
    {
      /* Woo! Got one. Look for "this dir" in the entries hash.  */
      entry_name = "";
    }

  if (dir_access == NULL)
    {
      /* Early exit.  */
      *entry = NULL;
      return SVN_NO_ERROR;
    }

  /* Load an entries hash, and cache it into DIR_ACCESS. Go ahead and
     fetch all entries here (optimization) since we know how to filter
     out a "hidden" node.  */
  SVN_ERR(svn_wc__entries_read_internal(&entries, dir_access, TRUE, pool));
  *entry = svn_hash_gets(entries, entry_name);

  if (!show_hidden && *entry != NULL)
    {
      svn_boolean_t hidden;

      SVN_ERR(svn_wc__entry_is_hidden(&hidden, *entry));
      if (hidden)
        *entry = NULL;
    }

  return SVN_NO_ERROR;
}