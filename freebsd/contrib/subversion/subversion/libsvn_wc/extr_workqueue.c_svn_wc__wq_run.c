#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ used; int /*<<< orphan*/ * record_map; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {char* data; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_DBG (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CANCELLED ; 
 int /*<<< orphan*/  SVN_ERR_WC_BAD_ADM_LOG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * dispatch_work_item (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  svn_cstring_atoi (int*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wq_fetch_next (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wq_record_and_fetch_next (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__wq_run(svn_wc__db_t *db,
               const char *wri_abspath,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_uint64_t last_id = 0;
  work_item_baton_t wib = { 0 };
  wib.result_pool = svn_pool_create(scratch_pool);

#ifdef SVN_DEBUG_WORK_QUEUE
  SVN_DBG(("wq_run: wri='%s'\n", wri_abspath));
  {
    static int count = 0;
    const char *count_env_var = getenv("SVN_DEBUG_WORK_QUEUE");
    int count_env_val;

    SVN_ERR(svn_cstring_atoi(&count_env_val, count_env_var));

    if (count_env_var && ++count == count_env_val)
      return svn_error_create(SVN_ERR_CANCELLED, NULL, "fake cancel");
  }
#endif

  while (TRUE)
    {
      apr_uint64_t id;
      svn_skel_t *work_item;
      svn_error_t *err;

      svn_pool_clear(iterpool);

      if (! wib.used)
        {
          /* Make sure to do this *early* in the loop iteration. There may
             be a LAST_ID that needs to be marked as completed, *before* we
             start worrying about anything else.  */
          SVN_ERR(svn_wc__db_wq_fetch_next(&id, &work_item, db, wri_abspath,
                                           last_id, iterpool, iterpool));
        }
      else
        {
          /* Make sure to do this *early* in the loop iteration. There may
             be a LAST_ID that needs to be marked as completed, *before* we
             start worrying about anything else.  */
          SVN_ERR(svn_wc__db_wq_record_and_fetch_next(&id, &work_item,
                                                      db, wri_abspath,
                                                      last_id, wib.record_map,
                                                      iterpool,
                                                      wib.result_pool));

          svn_pool_clear(wib.result_pool);
          wib.record_map = NULL;
          wib.used = FALSE;
        }

      /* Stop work queue processing, if requested. A future 'svn cleanup'
         should be able to continue the processing. Note that we may
         have WORK_ITEM, but we'll just skip its processing for now.  */
      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      /* If we have a WORK_ITEM, then process the sucker. Otherwise,
         we're done.  */
      if (work_item == NULL)
        break;

      err = dispatch_work_item(&wib, db, wri_abspath, work_item,
                               cancel_func, cancel_baton, iterpool);
      if (err)
        {
          const char *skel = svn_skel__unparse(work_item, scratch_pool)->data;

          return svn_error_createf(SVN_ERR_WC_BAD_ADM_LOG, err,
                                   _("Failed to run the WC DB work queue "
                                     "associated with '%s', work item %d %s"),
                                   svn_dirent_local_style(wri_abspath,
                                                          scratch_pool),
                                   (int)id, skel);
        }

      /* The work item finished without error. Mark it completed
         in the next loop.  */
      last_id = id;
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}