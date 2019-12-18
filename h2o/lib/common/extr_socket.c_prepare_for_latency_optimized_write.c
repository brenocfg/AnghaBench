#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int notsent_is_minimized; int suggested_tls_payload_size; int suggested_write_size; int /*<<< orphan*/  state; } ;
struct TYPE_12__ {TYPE_1__ _latency_optimization; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_13__ {int min_rtt; int max_additional_delay; int max_cwnd; } ;
typedef  TYPE_4__ h2o_socket_latency_optimization_conditions_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DETERMINED ; 
 int SIZE_MAX ; 
 int calc_suggested_tls_payload_size (TYPE_2__*,int) ; 
 int /*<<< orphan*/  disable_latency_optimized_write (TYPE_2__*,int (*) (TYPE_2__*,unsigned int)) ; 

__attribute__((used)) static inline void prepare_for_latency_optimized_write(h2o_socket_t *sock,
                                                       const h2o_socket_latency_optimization_conditions_t *conditions, uint32_t rtt,
                                                       uint32_t mss, uint32_t cwnd_size, uint32_t cwnd_avail, uint64_t loop_time,
                                                       int (*adjust_notsent_lowat)(h2o_socket_t *, unsigned))
{
    /* check RTT */
    if (rtt < conditions->min_rtt * (uint64_t)1000)
        goto Disable;
    if (rtt * conditions->max_additional_delay < loop_time * 1000 * 100)
        goto Disable;

    /* latency-optimization is enabled */
    sock->_latency_optimization.state = H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DETERMINED;

    /* no need to:
     *   1) adjust the write size if single_write_size << cwnd_size
     *   2) align TLS record boundary to TCP packet boundary if packet loss-rate is low and BW isn't small (implied by cwnd size)
     */
    if (mss * cwnd_size < conditions->max_cwnd) {
        if (!sock->_latency_optimization.notsent_is_minimized) {
            if (adjust_notsent_lowat(sock, 1 /* cannot be set to zero on Linux */) != 0)
                goto Disable;
            sock->_latency_optimization.notsent_is_minimized = 1;
        }
        sock->_latency_optimization.suggested_tls_payload_size = calc_suggested_tls_payload_size(sock, mss);
        sock->_latency_optimization.suggested_write_size =
            cwnd_avail * (size_t)sock->_latency_optimization.suggested_tls_payload_size;
    } else {
        if (sock->_latency_optimization.notsent_is_minimized) {
            if (adjust_notsent_lowat(sock, 0) != 0)
                goto Disable;
            sock->_latency_optimization.notsent_is_minimized = 0;
        }
        sock->_latency_optimization.suggested_tls_payload_size = 16384;
        sock->_latency_optimization.suggested_write_size = SIZE_MAX;
    }
    return;

Disable:
    disable_latency_optimized_write(sock, adjust_notsent_lowat);
}