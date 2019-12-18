#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
struct TYPE_7__ {int /*<<< orphan*/  dir_data; int /*<<< orphan*/  state_pool; int /*<<< orphan*/  config; } ;
typedef  TYPE_2__ svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FORMAT_FROM_SDB ; 
 int /*<<< orphan*/  SDB_FILE ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_SQLITE_EXCLUSIVE ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_WORKING_COPY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  create_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 int svn_dirent_is_absolute (char const*) ; 
 scalar_t__ svn_dirent_is_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_wc__db_pdh_create_wcroot (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_init(svn_wc__db_t *db,
                const char *local_abspath,
                const char *repos_relpath,
                const char *repos_root_url,
                const char *repos_uuid,
                svn_revnum_t initial_rev,
                svn_depth_t depth,
                apr_pool_t *scratch_pool)
{
  svn_sqlite__db_t *sdb;
  apr_int64_t repos_id;
  apr_int64_t wc_id;
  svn_wc__db_wcroot_t *wcroot;
  svn_boolean_t sqlite_exclusive = FALSE;
  apr_int32_t sqlite_timeout = 0; /* default timeout */
  apr_hash_index_t *hi;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(repos_relpath != NULL);
  SVN_ERR_ASSERT(depth == svn_depth_empty
                 || depth == svn_depth_files
                 || depth == svn_depth_immediates
                 || depth == svn_depth_infinity);

  /* ### REPOS_ROOT_URL and REPOS_UUID may be NULL. ... more doc: tbd  */

  SVN_ERR(svn_config_get_bool(db->config, &sqlite_exclusive,
                              SVN_CONFIG_SECTION_WORKING_COPY,
                              SVN_CONFIG_OPTION_SQLITE_EXCLUSIVE,
                              FALSE));

  /* Create the SDB and insert the basic rows.  */
  SVN_ERR(create_db(&sdb, &repos_id, &wc_id, local_abspath, repos_root_url,
                    repos_uuid, SDB_FILE,
                    repos_relpath, initial_rev, depth, sqlite_exclusive,
                    sqlite_timeout,
                    db->state_pool, scratch_pool));

  /* Create the WCROOT for this directory.  */
  SVN_ERR(svn_wc__db_pdh_create_wcroot(&wcroot,
                        apr_pstrdup(db->state_pool, local_abspath),
                        sdb, wc_id, FORMAT_FROM_SDB,
                        FALSE /* auto-upgrade */,
                        db->state_pool, scratch_pool));

  /* Any previously cached children may now have a new WCROOT, most likely that
     of the new WCROOT, but there might be descendant directories that are their
     own working copy, in which case setting WCROOT to our new WCROOT might
     actually break things for those.

     Clearing is the safest thing we can do in this case, as a test would lead
     to unnecessary probing, while the standard code probes later anyway. So we
     only lose a bit of memory

     ### Perhaps we could check wcroot->abspath to detect which case we have
         where, but currently it is already very hard to trigger this from
         the short living 'svn' client. (GUI clients like TortoiseSVN are far
         more likely to get in these cases)
     */
  for (hi = apr_hash_first(scratch_pool, db->dir_data);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *abspath = apr_hash_this_key(hi);
      if (svn_dirent_is_ancestor(wcroot->abspath, abspath))
        svn_hash_sets(db->dir_data, abspath, NULL);
    }

  /* The WCROOT is complete. Stash it into DB.  */
  svn_hash_sets(db->dir_data, wcroot->abspath, wcroot);

  return SVN_NO_ERROR;
}