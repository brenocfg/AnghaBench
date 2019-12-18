#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ res; scalar_t__ req; } ;
struct st_h2o_http1client_t {int /*<<< orphan*/  sock; TYPE_1__ state; } ;

/* Variables and functions */
 scalar_t__ STREAM_STATE_CLOSED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_response(struct st_h2o_http1client_t *client)
{
    assert(client->state.res == STREAM_STATE_CLOSED);
    if (client->state.req == STREAM_STATE_CLOSED) {
        close_client(client);
    } else {
        h2o_socket_read_stop(client->sock);
    }
}