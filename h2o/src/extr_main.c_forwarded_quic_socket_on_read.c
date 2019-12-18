#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  super; } ;
struct TYPE_7__ {TYPE_1__ ctx; } ;
struct listener_ctx_t {TYPE_2__ http3; } ;
struct TYPE_8__ {struct listener_ctx_t* data; } ;
typedef  TYPE_3__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_http3_read_socket (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrite_forwarded_quic_datagram ; 

__attribute__((used)) static void forwarded_quic_socket_on_read(h2o_socket_t *sock, const char *err)
{
    struct listener_ctx_t *ctx = sock->data;
    h2o_http3_read_socket(&ctx->http3.ctx.super, sock, rewrite_forwarded_quic_datagram);
}