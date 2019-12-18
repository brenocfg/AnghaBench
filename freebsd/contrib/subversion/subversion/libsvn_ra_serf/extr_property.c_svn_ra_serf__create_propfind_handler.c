#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__prop_func_t ;
struct TYPE_7__ {char* method; char const* path; char* body_type; int /*<<< orphan*/  no_dav_headers; TYPE_2__* header_delegate_baton; int /*<<< orphan*/  header_delegate; TYPE_2__* body_delegate_baton; int /*<<< orphan*/  body_delegate; } ;
typedef  TYPE_1__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {char const* path; char const* depth; TYPE_1__* handler; int /*<<< orphan*/ * label; void* prop_func_baton; int /*<<< orphan*/  prop_func; int /*<<< orphan*/  const* find_props; } ;
typedef  TYPE_2__ propfind_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_propfind_body ; 
 int /*<<< orphan*/  propfind_closed ; 
 int /*<<< orphan*/  propfind_expected_status ; 
 int /*<<< orphan*/  propfind_opened ; 
 int /*<<< orphan*/  propfind_ttable ; 
 int /*<<< orphan*/  setup_propfind_headers ; 
 TYPE_1__* svn_ra_serf__create_expat_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__xml_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__create_propfind_handler(svn_ra_serf__handler_t **propfind_handler,
                                     svn_ra_serf__session_t *sess,
                                     const char *path,
                                     svn_revnum_t rev,
                                     const char *depth,
                                     const svn_ra_serf__dav_props_t *find_props,
                                     svn_ra_serf__prop_func_t prop_func,
                                     void *prop_func_baton,
                                     apr_pool_t *pool)
{
  propfind_context_t *new_prop_ctx;
  svn_ra_serf__handler_t *handler;
  svn_ra_serf__xml_context_t *xmlctx;

  new_prop_ctx = apr_pcalloc(pool, sizeof(*new_prop_ctx));

  new_prop_ctx->path = path;
  new_prop_ctx->find_props = find_props;
  new_prop_ctx->prop_func = prop_func;
  new_prop_ctx->prop_func_baton = prop_func_baton;
  new_prop_ctx->depth = depth;

  if (SVN_IS_VALID_REVNUM(rev))
    {
      new_prop_ctx->label = apr_ltoa(pool, rev);
    }
  else
    {
      new_prop_ctx->label = NULL;
    }

  xmlctx = svn_ra_serf__xml_context_create(propfind_ttable,
                                           propfind_opened,
                                           propfind_closed,
                                           NULL,
                                           new_prop_ctx,
                                           pool);
  handler = svn_ra_serf__create_expat_handler(sess, xmlctx,
                                              propfind_expected_status,
                                              pool);

  handler->method = "PROPFIND";
  handler->path = path;
  handler->body_delegate = create_propfind_body;
  handler->body_type = "text/xml";
  handler->body_delegate_baton = new_prop_ctx;
  handler->header_delegate = setup_propfind_headers;
  handler->header_delegate_baton = new_prop_ctx;

  handler->no_dav_headers = TRUE;

  new_prop_ctx->handler = handler;

  *propfind_handler = handler;

  return SVN_NO_ERROR;
}