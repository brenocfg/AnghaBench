#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; scalar_t__ priority; int /*<<< orphan*/  ssltunnel; scalar_t__ writing_started; int /*<<< orphan*/ * req_bkt; } ;
typedef  TYPE_2__ serf_request_t ;
typedef  int /*<<< orphan*/  serf_request_setup_t ;
struct TYPE_10__ {int dirty_conn; TYPE_1__* ctx; TYPE_2__* requests; } ;
typedef  TYPE_3__ serf_connection_t ;
struct TYPE_8__ {int dirty_pollset; } ;

/* Variables and functions */
 TYPE_2__* create_request (TYPE_3__*,int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static serf_request_t *
priority_request_create(serf_connection_t *conn,
                        int ssltunnelreq,
                        serf_request_setup_t setup,
                        void *setup_baton)
{
    serf_request_t *request;
    serf_request_t *iter, *prev;

    request = create_request(conn, setup, setup_baton,
                             1, /* priority */
                             ssltunnelreq);

    /* Link the new request after the last written request. */
    iter = conn->requests;
    prev = NULL;

    /* Find a request that has data which needs to be delivered. */
    while (iter != NULL && iter->req_bkt == NULL && iter->writing_started) {
        prev = iter;
        iter = iter->next;
    }

    /* A CONNECT request to setup an ssltunnel has absolute priority over all
       other requests on the connection, so:
       a. add it first to the queue 
       b. ensure that other priority requests are added after the CONNECT
          request */
    if (!request->ssltunnel) {
        /* Advance to next non priority request */
        while (iter != NULL && iter->priority) {
            prev = iter;
            iter = iter->next;
        }
    }

    if (prev) {
        request->next = iter;
        prev->next = request;
    } else {
        request->next = iter;
        conn->requests = request;
    }

    /* Ensure our pollset becomes writable in context run */
    conn->ctx->dirty_pollset = 1;
    conn->dirty_conn = 1;

    return request;
}