#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  timeout_entry; TYPE_4__* ctx; TYPE_3__** sock; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ h2o_tunnel_t ;
struct TYPE_15__ {TYPE_1__* input; TYPE_2__* data; } ;
typedef  TYPE_3__ h2o_socket_t ;
struct TYPE_16__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_4__ h2o_context_t ;
struct TYPE_13__ {scalar_t__ size; } ;

/* Variables and functions */
 TYPE_2__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_3__*,int /*<<< orphan*/  (*) (TYPE_3__*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  h2o_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_read (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_timeout ; 

h2o_tunnel_t *h2o_tunnel_establish(h2o_context_t *ctx, h2o_socket_t *sock1, h2o_socket_t *sock2, uint64_t timeout)
{
    h2o_tunnel_t *tunnel = h2o_mem_alloc(sizeof(*tunnel));
    tunnel->ctx = ctx;
    tunnel->timeout = timeout;
    tunnel->sock[0] = sock1;
    tunnel->sock[1] = sock2;
    sock1->data = tunnel;
    sock2->data = tunnel;
    h2o_timer_init(&tunnel->timeout_entry, on_timeout);
    h2o_timer_link(tunnel->ctx->loop, timeout, &tunnel->timeout_entry);

    /* Bring up the tunnel. Note. Upstream always ready first. */
    if (sock2->input->size)
        on_read(sock2, NULL);
    if (sock1->input->size)
        on_read(sock1, NULL);
    h2o_socket_read_start(sock2, on_read);
    h2o_socket_read_start(sock1, on_read);

    return tunnel;
}