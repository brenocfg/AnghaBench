#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * pool; void* activity_collection_url; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {void* activity_collection; TYPE_5__* handler; } ;
typedef  TYPE_3__ options_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int code; } ;
struct TYPE_13__ {TYPE_1__ sline; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  create_options_req (TYPE_3__**,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_5__*) ; 

svn_error_t *
svn_ra_serf__v1_get_activity_collection(const char **activity_url,
                                        svn_ra_serf__session_t *session,
                                        apr_pool_t *result_pool,
                                        apr_pool_t *scratch_pool)
{
  options_context_t *opt_ctx;

  SVN_ERR_ASSERT(!SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session));

  if (session->activity_collection_url)
    {
      *activity_url = apr_pstrdup(result_pool,
                                  session->activity_collection_url);
      return SVN_NO_ERROR;
    }

  SVN_ERR(create_options_req(&opt_ctx, session, scratch_pool));
  SVN_ERR(svn_ra_serf__context_run_one(opt_ctx->handler, scratch_pool));

  if (opt_ctx->handler->sline.code != 200)
    return svn_error_trace(svn_ra_serf__unexpected_status(opt_ctx->handler));

  /* Cache the result. */
  if (opt_ctx->activity_collection)
    {
      session->activity_collection_url =
                    apr_pstrdup(session->pool, opt_ctx->activity_collection);
    }
  else
    {
      return svn_error_create(SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED, NULL,
                              _("The OPTIONS response did not include the "
                                "requested activity-collection-set value"));
    }

  *activity_url = apr_pstrdup(result_pool, opt_ctx->activity_collection);

  return SVN_NO_ERROR;

}