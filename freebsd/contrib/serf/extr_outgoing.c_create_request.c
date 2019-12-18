#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int priority; int ssltunnel; int /*<<< orphan*/ * auth_baton; int /*<<< orphan*/ * next; scalar_t__ writing_started; int /*<<< orphan*/ * resp_bkt; int /*<<< orphan*/ * req_bkt; int /*<<< orphan*/ * respool; int /*<<< orphan*/ * handler; void* setup_baton; int /*<<< orphan*/  setup; TYPE_2__* conn; } ;
typedef  TYPE_1__ serf_request_t ;
typedef  int /*<<< orphan*/  serf_request_setup_t ;
struct TYPE_7__ {int /*<<< orphan*/  allocator; } ;
typedef  TYPE_2__ serf_connection_t ;

/* Variables and functions */
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static serf_request_t *
create_request(serf_connection_t *conn,
               serf_request_setup_t setup,
               void *setup_baton,
               int priority,
               int ssltunnel)
{
    serf_request_t *request;

    request = serf_bucket_mem_alloc(conn->allocator, sizeof(*request));
    request->conn = conn;
    request->setup = setup;
    request->setup_baton = setup_baton;
    request->handler = NULL;
    request->respool = NULL;
    request->req_bkt = NULL;
    request->resp_bkt = NULL;
    request->priority = priority;
    request->writing_started = 0;
    request->ssltunnel = ssltunnel;
    request->next = NULL;
    request->auth_baton = NULL;

    return request;
}