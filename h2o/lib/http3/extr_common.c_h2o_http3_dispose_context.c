#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
struct TYPE_5__ {int /*<<< orphan*/  conns_accepting; int /*<<< orphan*/  conns_by_id; TYPE_1__ sock; int /*<<< orphan*/  clients; } ;
typedef  TYPE_2__ h2o_http3_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_destroy_h2o_http3_acceptmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_destroy_h2o_http3_idmap (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_size (int /*<<< orphan*/ ) ; 

void h2o_http3_dispose_context(h2o_http3_ctx_t *ctx)
{
    assert(kh_size(ctx->conns_by_id) == 0);
    assert(kh_size(ctx->conns_accepting) == 0);
    assert(h2o_linklist_is_empty(&ctx->clients));

    h2o_socket_close(ctx->sock.sock);
    kh_destroy_h2o_http3_idmap(ctx->conns_by_id);
    kh_destroy_h2o_http3_acceptmap(ctx->conns_accepting);
}