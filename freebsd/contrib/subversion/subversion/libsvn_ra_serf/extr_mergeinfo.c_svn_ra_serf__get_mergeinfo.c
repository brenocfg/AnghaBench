#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_12__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
struct TYPE_11__ {int code; } ;
struct TYPE_13__ {char* method; char const* path; char* body_type; TYPE_1__ sline; TYPE_4__* body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/ * result_catalog; int /*<<< orphan*/  include_descendants; int /*<<< orphan*/  inherit; int /*<<< orphan*/  revision; int /*<<< orphan*/  const* paths; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_4__ mergeinfo_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_mergeinfo_body ; 
 int /*<<< orphan*/  mergeinfo_closed ; 
 int /*<<< orphan*/  mergeinfo_ttable ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_stable_url (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_mergeinfo(svn_ra_session_t *ra_session,
                           svn_mergeinfo_catalog_t *catalog,
                           const apr_array_header_t *paths,
                           svn_revnum_t revision,
                           svn_mergeinfo_inheritance_t inherit,
                           svn_boolean_t include_descendants,
                           apr_pool_t *pool)
{
  mergeinfo_context_t *mergeinfo_ctx;
  svn_ra_serf__session_t *session = ra_session->priv;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;
  const char *path;

  *catalog = NULL;

  SVN_ERR(svn_ra_serf__get_stable_url(&path, NULL /* latest_revnum */,
                                      session,
                                      NULL /* url */, revision,
                                      pool, pool));

  mergeinfo_ctx = apr_pcalloc(pool, sizeof(*mergeinfo_ctx));
  mergeinfo_ctx->pool = pool;
  mergeinfo_ctx->result_catalog = apr_hash_make(pool);
  mergeinfo_ctx->paths = paths;
  mergeinfo_ctx->revision = revision;
  mergeinfo_ctx->inherit = inherit;
  mergeinfo_ctx->include_descendants = include_descendants;

  xmlctx = svn_ra_serf__xml_context_create(mergeinfo_ttable,
                                           NULL, mergeinfo_closed, NULL,
                                           mergeinfo_ctx,
                                           pool);
  handler = svn_ra_serf__create_expat_handler(session, xmlctx, NULL, pool);

  handler->method = "REPORT";
  handler->path = path;

  handler->body_delegate = create_mergeinfo_body;
  handler->body_delegate_baton = mergeinfo_ctx;
  handler->body_type = "text/xml";

  SVN_ERR(svn_ra_serf__context_run_one(handler, pool));

  if (handler->sline.code != 200)
    SVN_ERR(svn_ra_serf__unexpected_status(handler));

  if (apr_hash_count(mergeinfo_ctx->result_catalog))
    *catalog = mergeinfo_ctx->result_catalog;

  return SVN_NO_ERROR;
}