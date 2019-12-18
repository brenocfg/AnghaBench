#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_upgrade_get_repos_info_t ;
struct TYPE_21__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  repos; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct upgrade_data_t {int /*<<< orphan*/  sdb; int /*<<< orphan*/  root_abspath; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  repos_id; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM_LOG ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/  SVN_ERR_WC_UNSUPPORTED_FORMAT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC_ENTRY_THIS_DIR ; 
 int SVN_WC__WCPROPS_LOST ; 
 int SVN_WC__WCPROPS_MANY_FILES_VERSION ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* create_physical_lock (char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ensure_repos_info (TYPE_1__*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* migrate_props (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* migrate_text_bases (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* read_many_wcprops (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* read_wcprops (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_get_longest_ancestor (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_quick_wrap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 char* svn_wc__adm_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__read_entries_old (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__write_upgraded_entries (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* upgrade_apply_dav_cache (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
upgrade_to_wcng(void **dir_baton,
                void *parent_baton,
                svn_wc__db_t *db,
                const char *dir_abspath,
                int old_format,
                apr_int64_t wc_id,
                svn_wc_upgrade_get_repos_info_t repos_info_func,
                void *repos_info_baton,
                apr_hash_t *repos_cache,
                const struct upgrade_data_t *data,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  const char *logfile_path = svn_wc__adm_child(dir_abspath, ADM_LOG,
                                               scratch_pool);
  svn_node_kind_t logfile_on_disk_kind;
  apr_hash_t *entries;
  svn_wc_entry_t *this_dir;
  const char *old_wcroot_abspath, *dir_relpath;
  apr_hash_t *text_bases_info;
  svn_error_t *err;

  /* Don't try to mess with the WC if there are old log files left. */

  /* Is the (first) log file present?  */
  SVN_ERR(svn_io_check_path(logfile_path, &logfile_on_disk_kind,
                            scratch_pool));
  if (logfile_on_disk_kind == svn_node_file)
    return svn_error_create(SVN_ERR_WC_UNSUPPORTED_FORMAT, NULL,
                            _("Cannot upgrade with existing logs; run a "
                              "cleanup operation on this working copy using "
                              "a client version which is compatible with this "
                              "working copy's format (such as the version "
                              "you are upgrading from), then retry the "
                              "upgrade with the current version"));

  /* Lock this working copy directory, or steal an existing lock. Do this
     BEFORE we read the entries. We don't want another process to modify the
     entries after we've read them into memory.  */
  SVN_ERR(create_physical_lock(dir_abspath, scratch_pool));

  /* What's going on here?
   *
   * We're attempting to upgrade an older working copy to the new wc-ng format.
   * The semantics and storage mechanisms between the two are vastly different,
   * so it's going to be a bit painful.  Here's a plan for the operation:
   *
   * 1) Read the old 'entries' using the old-format reader.
   *
   * 2) Create the new DB if it hasn't already been created.
   *
   * 3) Use our compatibility code for writing entries to fill out the (new)
   *    DB state.  Use the remembered checksums, since an entry has only the
   *    MD5 not the SHA1 checksum, and in the case of a revert-base doesn't
   *    even have that.
   *
   * 4) Convert wcprop to the wc-ng format
   *
   * 5) Migrate regular properties to the WC-NG DB.
   */

  /***** ENTRIES - READ *****/
  SVN_ERR(svn_wc__read_entries_old(&entries, dir_abspath,
                                   scratch_pool, scratch_pool));

  this_dir = svn_hash_gets(entries, SVN_WC_ENTRY_THIS_DIR);
  SVN_ERR(ensure_repos_info(this_dir, dir_abspath,
                            repos_info_func, repos_info_baton,
                            repos_cache,
                            scratch_pool, scratch_pool));

  /* Cache repos UUID pairs for when a subdir doesn't have this information */
  if (!svn_hash_gets(repos_cache, this_dir->repos))
    {
      apr_pool_t *hash_pool = apr_hash_pool_get(repos_cache);

      svn_hash_sets(repos_cache,
                    apr_pstrdup(hash_pool, this_dir->repos),
                    apr_pstrdup(hash_pool, this_dir->uuid));
    }

  old_wcroot_abspath = svn_dirent_get_longest_ancestor(dir_abspath,
                                                       data->root_abspath,
                                                       scratch_pool);
  dir_relpath = svn_dirent_skip_ancestor(old_wcroot_abspath, dir_abspath);

  /***** TEXT BASES *****/
  SVN_ERR(migrate_text_bases(&text_bases_info, dir_abspath, data->root_abspath,
                             data->sdb, scratch_pool, scratch_pool));

  /***** ENTRIES - WRITE *****/
  err = svn_wc__write_upgraded_entries(dir_baton, parent_baton, db, data->sdb,
                                       data->repos_id, data->wc_id,
                                       dir_abspath, data->root_abspath,
                                       entries, text_bases_info,
                                       result_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_WC_CORRUPT)
    return svn_error_quick_wrap(err,
                                _("This working copy is corrupt and "
                                  "cannot be upgraded. Please check out "
                                  "a new working copy."));
  else
    SVN_ERR(err);

  /***** WC PROPS *****/
  /* If we don't know precisely where the wcprops are, ignore them.  */
  if (old_format != SVN_WC__WCPROPS_LOST)
    {
      apr_hash_t *all_wcprops;

      if (old_format <= SVN_WC__WCPROPS_MANY_FILES_VERSION)
        SVN_ERR(read_many_wcprops(&all_wcprops, dir_abspath,
                                  scratch_pool, scratch_pool));
      else
        SVN_ERR(read_wcprops(&all_wcprops, dir_abspath,
                             scratch_pool, scratch_pool));

      SVN_ERR(upgrade_apply_dav_cache(data->sdb, dir_relpath, wc_id,
                                      all_wcprops, scratch_pool));
    }

  /* Upgrade all the properties (including "this dir").

     Note: this must come AFTER the entries have been migrated into the
     database. The upgrade process needs the children in BASE_NODE and
     WORKING_NODE, and to examine the resultant WORKING state.  */
  SVN_ERR(migrate_props(dir_abspath, data->root_abspath, data->sdb, old_format,
                        wc_id, scratch_pool));

  return SVN_NO_ERROR;
}