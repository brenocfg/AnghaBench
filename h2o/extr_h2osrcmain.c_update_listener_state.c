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
struct listener_ctx_t {int /*<<< orphan*/  sock; } ;
struct TYPE_2__ {scalar_t__ max_connections; size_t num_listeners; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ h2o_socket_is_reading (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ num_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_accept ; 

__attribute__((used)) static void update_listener_state(struct listener_ctx_t *listeners)
{
    size_t i;

    if (num_connections(0) < conf.max_connections) {
        for (i = 0; i != conf.num_listeners; ++i) {
            if (!h2o_socket_is_reading(listeners[i].sock))
                h2o_socket_read_start(listeners[i].sock, on_accept);
        }
    } else {
        for (i = 0; i != conf.num_listeners; ++i) {
            if (h2o_socket_is_reading(listeners[i].sock))
                h2o_socket_read_stop(listeners[i].sock);
        }
    }
}