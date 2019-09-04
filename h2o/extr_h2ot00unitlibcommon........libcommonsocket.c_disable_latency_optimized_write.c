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
struct TYPE_6__ {int suggested_tls_payload_size; int /*<<< orphan*/  suggested_write_size; int /*<<< orphan*/  state; scalar_t__ notsent_is_minimized; } ;
struct TYPE_7__ {TYPE_1__ _latency_optimization; } ;
typedef  TYPE_2__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DISABLED ; 
 int /*<<< orphan*/  SIZE_MAX ; 

__attribute__((used)) static void disable_latency_optimized_write(h2o_socket_t *sock, int (*adjust_notsent_lowat)(h2o_socket_t *, unsigned))
{
    if (sock->_latency_optimization.notsent_is_minimized) {
        adjust_notsent_lowat(sock, 0);
        sock->_latency_optimization.notsent_is_minimized = 0;
    }
    sock->_latency_optimization.state = H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DISABLED;
    sock->_latency_optimization.suggested_tls_payload_size = 16384;
    sock->_latency_optimization.suggested_write_size = SIZE_MAX;
}