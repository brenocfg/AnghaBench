#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  void* svn_boolean_t ;
struct TYPE_10__ {char const* repos_root_url; char const* repos_uuid; char const* repos_relpath; char const* changed_author; char const* recorded_repos_relpath; int /*<<< orphan*/  const* work_items; int /*<<< orphan*/  const* conflict; void* keep_recorded_info; int /*<<< orphan*/ * new_actual_props; void* update_actual_props; void* recorded_revision; void* recorded_peg_revision; void* record_ancestor_relpath; int /*<<< orphan*/  const* dav_cache; int /*<<< orphan*/  const* checksum; int /*<<< orphan*/  changed_date; void* changed_rev; int /*<<< orphan*/ * iprops; int /*<<< orphan*/  const* props; void* revision; int /*<<< orphan*/  presence; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ insert_external_baton_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  blank_ieb (TYPE_2__*) ; 
 int /*<<< orphan*/  insert_external_node (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_ancestor (int /*<<< orphan*/ ,char const*) ; 
 void* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_external_add_file(svn_wc__db_t *db,
                             const char *local_abspath,
                             const char *wri_abspath,

                             const char *repos_relpath,
                             const char *repos_root_url,
                             const char *repos_uuid,
                             svn_revnum_t revision,

                             const apr_hash_t *props,
                             apr_array_header_t *iprops,

                             svn_revnum_t changed_rev,
                             apr_time_t changed_date,
                             const char *changed_author,

                             const svn_checksum_t *checksum,

                             const apr_hash_t *dav_cache,

                             const char *record_ancestor_abspath,
                             const char *recorded_repos_relpath,
                             svn_revnum_t recorded_peg_revision,
                             svn_revnum_t recorded_revision,

                             svn_boolean_t update_actual_props,
                             apr_hash_t *new_actual_props,

                             svn_boolean_t keep_recorded_info,
                             const svn_skel_t *conflict,
                             const svn_skel_t *work_items,
                             apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  insert_external_baton_t ieb;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  if (! wri_abspath)
    wri_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_ERR_ASSERT(svn_dirent_is_ancestor(wcroot->abspath,
                                        record_ancestor_abspath));

  SVN_ERR_ASSERT(svn_dirent_is_ancestor(wcroot->abspath, local_abspath));

  local_relpath = svn_dirent_skip_ancestor(wcroot->abspath, local_abspath);

  blank_ieb(&ieb);

  ieb.kind = svn_node_file;
  ieb.presence = svn_wc__db_status_normal;

  ieb.repos_root_url = repos_root_url;
  ieb.repos_uuid = repos_uuid;

  ieb.repos_relpath = repos_relpath;
  ieb.revision = revision;

  ieb.props = props;
  ieb.iprops = iprops;

  ieb.changed_rev = changed_rev;
  ieb.changed_date = changed_date;
  ieb.changed_author = changed_author;

  ieb.checksum = checksum;

  ieb.dav_cache = dav_cache;

  ieb.record_ancestor_relpath = svn_dirent_skip_ancestor(
                                                wcroot->abspath,
                                                record_ancestor_abspath);
  ieb.recorded_repos_relpath = recorded_repos_relpath;
  ieb.recorded_peg_revision = recorded_peg_revision;
  ieb.recorded_revision = recorded_revision;

  ieb.update_actual_props = update_actual_props;
  ieb.new_actual_props = new_actual_props;

  ieb.keep_recorded_info = keep_recorded_info;

  ieb.conflict = conflict;
  ieb.work_items = work_items;

  SVN_WC__DB_WITH_TXN(
            insert_external_node(&ieb, wcroot, local_relpath, scratch_pool),
            wcroot);

  return SVN_NO_ERROR;
}