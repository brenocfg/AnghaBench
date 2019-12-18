#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_response_handler_t ;
typedef  int /*<<< orphan*/  serf_response_acceptor_t ;
struct TYPE_3__ {int async_responses; void* async_handler_baton; int /*<<< orphan*/  async_handler; void* async_acceptor_baton; int /*<<< orphan*/  async_acceptor; } ;
typedef  TYPE_1__ serf_connection_t ;

/* Variables and functions */

void serf_connection_set_async_responses(
    serf_connection_t *conn,
    serf_response_acceptor_t acceptor,
    void *acceptor_baton,
    serf_response_handler_t handler,
    void *handler_baton)
{
    conn->async_responses = 1;
    conn->async_acceptor = acceptor;
    conn->async_acceptor_baton = acceptor_baton;
    conn->async_handler = handler;
    conn->async_handler_baton = handler_baton;
}