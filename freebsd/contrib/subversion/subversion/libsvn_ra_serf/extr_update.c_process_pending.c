#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * spillbuf; TYPE_1__* report; } ;
typedef  TYPE_2__ update_delay_baton_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {scalar_t__ num_active_fetches; scalar_t__ num_active_propfinds; int /*<<< orphan*/  report_received; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ REQUEST_COUNT_TO_RESUME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* process_buffer (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_allocator_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__read (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
process_pending(update_delay_baton_t *udb,
                apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = NULL;
  serf_bucket_alloc_t *alloc = NULL;

  while ((udb->report->num_active_fetches + udb->report->num_active_propfinds)
            < REQUEST_COUNT_TO_RESUME)
    {
      const char *data;
      apr_size_t len;
      svn_boolean_t at_eof;
      svn_error_t *err;

      if (!iterpool)
        {
          iterpool = svn_pool_create(scratch_pool);
          alloc = serf_bucket_allocator_create(scratch_pool, NULL, NULL);
        }
      else
        svn_pool_clear(iterpool);

      SVN_ERR(svn_spillbuf__read(&data, &len, udb->spillbuf, iterpool));

      if (data == NULL && !udb->report->report_received)
        break;
      else if (data == NULL)
        at_eof = TRUE;
      else
        at_eof = FALSE;

      err = process_buffer(udb, NULL /* allowed? */, data, len,
                           at_eof, alloc, iterpool);

      if (err && APR_STATUS_IS_EAGAIN(err->apr_err))
        {
          svn_error_clear(err); /* Throttling is working */
        }
      else if (err && APR_STATUS_IS_EOF(err->apr_err))
        {
          svn_error_clear(err);

          svn_pool_destroy(iterpool);
          udb->spillbuf = NULL;
          return SVN_NO_ERROR;
        }
      else if (err)
        return svn_error_trace(err);
    }

  if (iterpool)
    svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}