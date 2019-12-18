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
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * serf_bucket_barrier_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_response_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_request_get_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static serf_bucket_t *
accept_response(serf_request_t *request,
                serf_bucket_t *stream,
                void *acceptor_baton,
                apr_pool_t *pool)
{
  /* svn_ra_serf__handler_t *handler = acceptor_baton; */
  serf_bucket_t *c;
  serf_bucket_alloc_t *bkt_alloc;

  bkt_alloc = serf_request_get_alloc(request);
  c = serf_bucket_barrier_create(stream, bkt_alloc);

  return serf_bucket_response_create(c, bkt_alloc);
}