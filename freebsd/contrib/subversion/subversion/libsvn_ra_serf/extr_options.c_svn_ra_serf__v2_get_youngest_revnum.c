#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  youngest_rev; TYPE_3__* handler; } ;
typedef  TYPE_2__ options_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int code; } ;
struct TYPE_8__ {TYPE_1__ sline; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_options_req (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 

svn_error_t *
svn_ra_serf__v2_get_youngest_revnum(svn_revnum_t *youngest,
                                    svn_ra_serf__session_t *session,
                                    apr_pool_t *scratch_pool)
{
  options_context_t *opt_ctx;

  SVN_ERR_ASSERT(SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session));

  SVN_ERR(create_options_req(&opt_ctx, session, scratch_pool));
  SVN_ERR(svn_ra_serf__context_run_one(opt_ctx->handler, scratch_pool));

  if (opt_ctx->handler->sline.code != 200)
    return svn_error_trace(svn_ra_serf__unexpected_status(opt_ctx->handler));

  if (! SVN_IS_VALID_REVNUM(opt_ctx->youngest_rev))
    return svn_error_create(SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED, NULL,
                            _("The OPTIONS response did not include "
                              "the youngest revision"));

  *youngest = opt_ctx->youngest_rev;

  return SVN_NO_ERROR;
}