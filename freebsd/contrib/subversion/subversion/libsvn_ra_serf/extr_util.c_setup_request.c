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
struct TYPE_4__ {int /*<<< orphan*/  header_delegate_baton; int /*<<< orphan*/  (* header_delegate ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  no_dav_headers; int /*<<< orphan*/  body_type; int /*<<< orphan*/  path; int /*<<< orphan*/  method; TYPE_2__* session; scalar_t__ custom_accept_encoding; int /*<<< orphan*/  body_delegate_baton; int /*<<< orphan*/  (* body_delegate ) (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {scalar_t__ using_compression; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * serf_request_get_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_serf_req (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_tristate_false ; 

__attribute__((used)) static svn_error_t *
setup_request(serf_request_t *request,
              svn_ra_serf__handler_t *handler,
              serf_bucket_t **req_bkt,
              apr_pool_t *request_pool,
              apr_pool_t *scratch_pool)
{
  serf_bucket_t *body_bkt;
  serf_bucket_t *headers_bkt;
  const char *accept_encoding;

  if (handler->body_delegate)
    {
      serf_bucket_alloc_t *bkt_alloc = serf_request_get_alloc(request);

      SVN_ERR(handler->body_delegate(&body_bkt, handler->body_delegate_baton,
                                     bkt_alloc, request_pool, scratch_pool));
    }
  else
    {
      body_bkt = NULL;
    }

  if (handler->custom_accept_encoding)
    {
      accept_encoding = NULL;
    }
  else if (handler->session->using_compression != svn_tristate_false)
    {
      /* Accept gzip compression if enabled. */
      accept_encoding = "gzip";
    }
  else
    {
      accept_encoding = NULL;
    }

  SVN_ERR(setup_serf_req(request, req_bkt, &headers_bkt,
                         handler->session, handler->method, handler->path,
                         body_bkt, handler->body_type, accept_encoding,
                         !handler->no_dav_headers, request_pool,
                         scratch_pool));

  if (handler->header_delegate)
    {
      SVN_ERR(handler->header_delegate(headers_bkt,
                                       handler->header_delegate_baton,
                                       request_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}