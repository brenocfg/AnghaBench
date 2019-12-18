#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* report; scalar_t__ spillbuf; int /*<<< orphan*/  inner_handler_baton; TYPE_3__* (* inner_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ update_delay_baton_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {scalar_t__ num_active_fetches; scalar_t__ num_active_propfinds; void* report_received; int /*<<< orphan*/  pool; scalar_t__ send_all_mode; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 void* FALSE ; 
 int PARSE_CHUNK_SIZE ; 
 scalar_t__ REQUEST_COUNT_TO_RESUME ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  SPILLBUF_BLOCKSIZE ; 
 int /*<<< orphan*/  SPILLBUF_MAXBUFFSIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 void* TRUE ; 
 TYPE_3__* process_buffer (TYPE_2__*,int /*<<< orphan*/ *,char const*,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ serf_bucket_read (int /*<<< orphan*/ *,int,char const**,scalar_t__*) ; 
 int /*<<< orphan*/  serf_request_get_alloc (int /*<<< orphan*/ *) ; 
 TYPE_3__* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_spillbuf__create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_spillbuf__write (scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_delay_handler(serf_request_t *request,
                     serf_bucket_t *response,
                     void *handler_baton,
                     apr_pool_t *scratch_pool)
{
  update_delay_baton_t *udb = handler_baton;
  apr_status_t status;
  apr_pool_t *iterpool = NULL;

  if (! udb->spillbuf)
    {
      if (udb->report->send_all_mode)
        {
          /* Easy out... We only have one request, so avoid everything and just
             call the inner handler.

             We will always get in the loop (below) on the first chunk, as only
             the server can get us in true send-all mode */

          return svn_error_trace(udb->inner_handler(request, response,
                                                    udb->inner_handler_baton,
                                                    scratch_pool));
        }

      while ((udb->report->num_active_fetches + udb->report->num_active_propfinds)
                 < REQUEST_COUNT_TO_RESUME)
        {
          const char *data;
          apr_size_t len;
          svn_boolean_t at_eof = FALSE;
          svn_error_t *err;

          status = serf_bucket_read(response, PARSE_CHUNK_SIZE, &data, &len);
          if (SERF_BUCKET_READ_ERROR(status))
            return svn_ra_serf__wrap_err(status, NULL);
          else if (APR_STATUS_IS_EOF(status))
            udb->report->report_received = at_eof = TRUE;

          if (!iterpool)
            iterpool = svn_pool_create(scratch_pool);
          else
            svn_pool_clear(iterpool);

          if (len == 0 && !at_eof)
            return svn_ra_serf__wrap_err(status, NULL);

          err = process_buffer(udb, request, data, len, at_eof,
                               serf_request_get_alloc(request),
                               iterpool);

          if (err && SERF_BUCKET_READ_ERROR(err->apr_err))
            return svn_error_trace(err);
          else if (err && APR_STATUS_IS_EAGAIN(err->apr_err))
            {
              svn_error_clear(err); /* Throttling is working ok */
            }
          else if (err && (APR_STATUS_IS_EOF(err->apr_err)))
            {
              svn_pool_destroy(iterpool);
              return svn_error_trace(err); /* No buffering was necessary */
            }
          else
            {
              /* SERF_ERROR_WAIT_CONN should be impossible? */
              return svn_error_trace(err);
            }
        }

      /* Let's start using the spill infrastructure */
      udb->spillbuf = svn_spillbuf__create(SPILLBUF_BLOCKSIZE,
                                           SPILLBUF_MAXBUFFSIZE,
                                           udb->report->pool);
    }

  /* Read everything we can to a spillbuffer */
  do
    {
      const char *data;
      apr_size_t len;

      /* ### What blocksize should we pass? */
      status = serf_bucket_read(response, 8*PARSE_CHUNK_SIZE, &data, &len);

      if (!SERF_BUCKET_READ_ERROR(status))
        SVN_ERR(svn_spillbuf__write(udb->spillbuf, data, len, scratch_pool));
    }
  while (status == APR_SUCCESS);

  if (APR_STATUS_IS_EOF(status))
    udb->report->report_received = TRUE;

  /* We handle feeding the data from the main context loop, which will be right
     after processing the pending data */

  if (status)
    return svn_ra_serf__wrap_err(status, NULL);
  else
    return SVN_NO_ERROR;
}