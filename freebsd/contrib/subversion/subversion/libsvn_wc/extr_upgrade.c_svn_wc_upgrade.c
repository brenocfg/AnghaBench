#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_upgrade_get_repos_info_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_11__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  repos; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_12__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
struct upgrade_data_t {char const* root_abspath; int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  repos_id; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* PRISTINE_STORAGE_RELPATH ; 
 char* SDB_FILE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_WC_UPGRADE_REQUIRED ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_WC_ENTRY_THIS_DIR ; 
 int SVN_WC__VERSION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_repos_info (TYPE_1__*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_old_wcroot (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_child (char const*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_bump_format (int*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_upgrade_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_obtain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_release (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wq_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__ensure_directory (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__read_entries_old (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_move (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_postupgrade (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_upgraded_path ; 
 int /*<<< orphan*/  upgrade_working_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,struct upgrade_data_t*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_upgrade(svn_wc_context_t *wc_ctx,
               const char *local_abspath,
               svn_wc_upgrade_get_repos_info_t repos_info_func,
               void *repos_info_baton,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               svn_wc_notify_func2_t notify_func,
               void *notify_baton,
               apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db;
  struct upgrade_data_t data = { NULL };
  svn_skel_t *work_item, *work_items = NULL;
  const char *pristine_from, *pristine_to, *db_from, *db_to;
  apr_hash_t *repos_cache = apr_hash_make(scratch_pool);
  svn_wc_entry_t *this_dir;
  apr_hash_t *entries;
  const char *root_adm_abspath;
  svn_error_t *err;
  int result_format;
  svn_boolean_t bumped_format;

  /* Try upgrading a wc-ng-style working copy. */
  SVN_ERR(svn_wc__db_open(&db, NULL /* ### config */, TRUE, FALSE,
                          scratch_pool, scratch_pool));


  err = svn_wc__db_bump_format(&result_format, &bumped_format,
                               db, local_abspath,
                               scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_UPGRADE_REQUIRED)
        {
          return svn_error_trace(
                    svn_error_compose_create(
                            err,
                            svn_wc__db_close(db)));
        }

      svn_error_clear(err);
      /* Pre 1.7: Fall through */
    }
  else
    {
      /* Auto-upgrade worked! */
      SVN_ERR(svn_wc__db_close(db));

      SVN_ERR_ASSERT(result_format == SVN_WC__VERSION);

      if (bumped_format && notify_func)
        {
          svn_wc_notify_t *notify;

          notify = svn_wc_create_notify(local_abspath,
                                        svn_wc_notify_upgraded_path,
                                        scratch_pool);

          notify_func(notify_baton, notify, scratch_pool);
        }

      return SVN_NO_ERROR;
    }

  SVN_ERR(is_old_wcroot(local_abspath, scratch_pool));

  /* Given a pre-wcng root some/wc we create a temporary wcng in
     some/wc/.svn/tmp/wcng/wc.db and copy the metadata from one to the
     other, then the temporary wc.db file gets moved into the original
     root.  Until the wc.db file is moved the original working copy
     remains a pre-wcng and 'cleanup' with an old client will remove
     the partial upgrade.  Moving the wc.db file creates a wcng, and
     'cleanup' with a new client will complete any outstanding
     upgrade. */

  SVN_ERR(svn_wc__read_entries_old(&entries, local_abspath,
                                   scratch_pool, scratch_pool));

  this_dir = svn_hash_gets(entries, SVN_WC_ENTRY_THIS_DIR);
  SVN_ERR(ensure_repos_info(this_dir, local_abspath, repos_info_func,
                            repos_info_baton, repos_cache,
                            scratch_pool, scratch_pool));

  /* Cache repos UUID pairs for when a subdir doesn't have this information */
  if (!svn_hash_gets(repos_cache, this_dir->repos))
    svn_hash_sets(repos_cache,
                  apr_pstrdup(scratch_pool, this_dir->repos),
                  apr_pstrdup(scratch_pool, this_dir->uuid));

  /* Create the new DB in the temporary root wc/.svn/tmp/wcng/.svn */
  data.root_abspath = svn_dirent_join(svn_wc__adm_child(local_abspath, "tmp",
                                                        scratch_pool),
                                       "wcng", scratch_pool);
  root_adm_abspath = svn_wc__adm_child(data.root_abspath, "",
                                       scratch_pool);
  SVN_ERR(svn_io_remove_dir2(root_adm_abspath, TRUE, NULL, NULL,
                             scratch_pool));
  SVN_ERR(svn_wc__ensure_directory(root_adm_abspath, scratch_pool));

  /* Create an empty sqlite database for this directory and store it in DB. */
  SVN_ERR(svn_wc__db_upgrade_begin(&data.sdb,
                                   &data.repos_id, &data.wc_id,
                                   db, data.root_abspath,
                                   this_dir->repos, this_dir->uuid,
                                   scratch_pool));

  /* Migrate the entries over to the new database.
   ### We need to think about atomicity here.

   entries_write_new() writes in current format rather than
   f12. Thus, this function bumps a working copy all the way to
   current.  */
  SVN_ERR(svn_wc__db_wclock_obtain(db, data.root_abspath, 0, FALSE,
                                   scratch_pool));

  SVN_SQLITE__WITH_LOCK(
    upgrade_working_copy(NULL, db, local_abspath,
                         repos_info_func, repos_info_baton,
                         repos_cache, &data,
                         cancel_func, cancel_baton,
                         notify_func, notify_baton,
                         scratch_pool, scratch_pool),
    data.sdb);

  /* A workqueue item to move the pristine dir into place */
  pristine_from = svn_wc__adm_child(data.root_abspath, PRISTINE_STORAGE_RELPATH,
                                    scratch_pool);
  pristine_to = svn_wc__adm_child(local_abspath, PRISTINE_STORAGE_RELPATH,
                                  scratch_pool);
  SVN_ERR(svn_wc__ensure_directory(pristine_from, scratch_pool));
  SVN_ERR(svn_wc__wq_build_file_move(&work_item, db, local_abspath,
                                     pristine_from, pristine_to,
                                     scratch_pool, scratch_pool));
  work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);

  /* A workqueue item to remove pre-wcng metadata */
  SVN_ERR(svn_wc__wq_build_postupgrade(&work_item, scratch_pool));
  work_items = svn_wc__wq_merge(work_items, work_item, scratch_pool);
  SVN_ERR(svn_wc__db_wq_add(db, data.root_abspath, work_items, scratch_pool));

  SVN_ERR(svn_wc__db_wclock_release(db, data.root_abspath, scratch_pool));
  SVN_ERR(svn_wc__db_close(db));

  /* Renaming the db file is what makes the pre-wcng into a wcng */
  db_from = svn_wc__adm_child(data.root_abspath, SDB_FILE, scratch_pool);
  db_to = svn_wc__adm_child(local_abspath, SDB_FILE, scratch_pool);
  SVN_ERR(svn_io_file_rename2(db_from, db_to, FALSE, scratch_pool));

  /* Now we have a working wcng, tidy up the droppings */
  SVN_ERR(svn_wc__db_open(&db, NULL /* ### config */, FALSE, FALSE,
                          scratch_pool, scratch_pool));
  SVN_ERR(svn_wc__wq_run(db, local_abspath, cancel_func, cancel_baton,
                         scratch_pool));
  SVN_ERR(svn_wc__db_close(db));

  /* Should we have the workqueue remove this empty dir? */
  SVN_ERR(svn_io_remove_dir2(data.root_abspath, FALSE, NULL, NULL,
                             scratch_pool));

  return SVN_NO_ERROR;
}