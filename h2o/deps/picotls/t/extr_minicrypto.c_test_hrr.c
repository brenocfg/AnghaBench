#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sbuf_small ;
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_algorithm_t ;
struct TYPE_12__ {TYPE_1__** key_exchanges; int /*<<< orphan*/  member_3; int /*<<< orphan*/ ** member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ptls_context_t ;
struct TYPE_13__ {size_t off; int* base; } ;
typedef  TYPE_3__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  decbuf_small ;
typedef  int /*<<< orphan*/  cbuf_small ;
struct TYPE_11__ {scalar_t__ id; } ;

/* Variables and functions */
 int PTLS_ERROR_IN_PROGRESS ; 
 scalar_t__ PTLS_GROUP_SECP256R1 ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* ctx_peer ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int ptls_handshake (int /*<<< orphan*/ *,TYPE_3__*,int*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_minicrypto_cipher_suites ; 
 int /*<<< orphan*/  ptls_minicrypto_random_bytes ; 
 int /*<<< orphan*/  ptls_minicrypto_secp256r1 ; 
 int /*<<< orphan*/  ptls_minicrypto_x25519 ; 
 int /*<<< orphan*/ * ptls_new (TYPE_2__*,int) ; 
 int ptls_receive (int /*<<< orphan*/ *,TYPE_3__*,int*,size_t*) ; 
 int ptls_send (int /*<<< orphan*/ *,TYPE_3__*,char*,int) ; 

__attribute__((used)) static void test_hrr(void)
{
    ptls_key_exchange_algorithm_t *client_keyex[] = {&ptls_minicrypto_x25519, &ptls_minicrypto_secp256r1, NULL};
    ptls_context_t client_ctx = {ptls_minicrypto_random_bytes, &ptls_get_time, client_keyex, ptls_minicrypto_cipher_suites};
    ptls_t *client, *server;
    ptls_buffer_t cbuf, sbuf, decbuf;
    uint8_t cbuf_small[16384], sbuf_small[16384], decbuf_small[16384];
    size_t consumed;
    int ret;

    assert(ctx_peer->key_exchanges[0] != NULL && ctx_peer->key_exchanges[0]->id == PTLS_GROUP_SECP256R1);
    assert(ctx_peer->key_exchanges[1] == NULL);

    client = ptls_new(&client_ctx, 0);
    server = ptls_new(ctx_peer, 1);
    ptls_buffer_init(&cbuf, cbuf_small, sizeof(cbuf_small));
    ptls_buffer_init(&sbuf, sbuf_small, sizeof(sbuf_small));
    ptls_buffer_init(&decbuf, decbuf_small, sizeof(decbuf_small));

    ret = ptls_handshake(client, &cbuf, NULL, NULL, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);

    consumed = cbuf.off;
    ret = ptls_handshake(server, &sbuf, cbuf.base, &consumed, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);
    ok(consumed == cbuf.off);
    cbuf.off = 0;

    ok(sbuf.off > 5 + 4);
    ok(sbuf.base[5] == 2 /* PTLS_HANDSHAKE_TYPE_SERVER_HELLO (RETRY_REQUEST) */);

    consumed = sbuf.off;
    ret = ptls_handshake(client, &cbuf, sbuf.base, &consumed, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);
    ok(consumed == sbuf.off);
    sbuf.off = 0;

    ok(cbuf.off >= 5 + 4);
    ok(cbuf.base[5] == 1 /* PTLS_HANDSHAKE_TYPE_CLIENT_HELLO */);

    consumed = cbuf.off;
    ret = ptls_handshake(server, &sbuf, cbuf.base, &consumed, NULL);
    ok(ret == 0);
    ok(consumed == cbuf.off);
    cbuf.off = 0;

    ok(sbuf.off >= 5 + 4);
    ok(sbuf.base[5] == 2 /* PTLS_HANDSHAKE_TYPE_SERVER_HELLO */);

    consumed = sbuf.off;
    ret = ptls_handshake(client, &cbuf, sbuf.base, &consumed, NULL);
    ok(ret == 0);
    ok(consumed == sbuf.off);
    sbuf.off = 0;

    ret = ptls_send(client, &cbuf, "hello world", 11);
    ok(ret == 0);

    consumed = cbuf.off;
    ret = ptls_receive(server, &decbuf, cbuf.base, &consumed);
    ok(ret == 0);
    ok(consumed == cbuf.off);
    cbuf.off = 0;

    ok(decbuf.off == 11);
    ok(memcmp(decbuf.base, "hello world", 11) == 0);

    ptls_buffer_dispose(&decbuf);
    ptls_buffer_dispose(&sbuf);
    ptls_buffer_dispose(&cbuf);
    ptls_free(client);
    ptls_free(server);
}