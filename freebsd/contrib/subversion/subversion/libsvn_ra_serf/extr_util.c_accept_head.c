#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * accept_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_response_set_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static serf_bucket_t *
accept_head(serf_request_t *request,
            serf_bucket_t *stream,
            void *acceptor_baton,
            apr_pool_t *pool)
{
  /* svn_ra_serf__handler_t *handler = acceptor_baton; */
  serf_bucket_t *response;

  response = accept_response(request, stream, acceptor_baton, pool);

  /* We know we shouldn't get a response body. */
  serf_bucket_response_set_head(response);

  return response;
}