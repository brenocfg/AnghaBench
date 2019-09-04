#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
struct TYPE_6__ {size_t off; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int PTLS_ERROR_IN_PROGRESS ; 
 int PTLS_ERROR_STATELESS_RETRY ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  ctx_peer ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_free (int /*<<< orphan*/ *) ; 
 int ptls_handshake (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_new (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ptls_t *stateless_hrr_prepare(ptls_buffer_t *sbuf, ptls_handshake_properties_t *server_hs_prop)
{
    ptls_t *client = ptls_new(ctx, 0), *server = ptls_new(ctx_peer, 1);
    ptls_buffer_t cbuf;
    size_t consumed;
    int ret;

    ptls_buffer_init(&cbuf, "", 0);
    ptls_buffer_init(sbuf, "", 0);

    ret = ptls_handshake(client, &cbuf, NULL, NULL, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);

    consumed = cbuf.off;
    ret = ptls_handshake(server, sbuf, cbuf.base, &consumed, server_hs_prop);
    ok(ret == PTLS_ERROR_STATELESS_RETRY);

    ptls_buffer_dispose(&cbuf);
    ptls_free(server);

    return client;
}