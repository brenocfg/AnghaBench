#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_kx_PRIMITIVE ; 
 int crypto_kx_PUBLICKEYBYTES ; 
 int crypto_kx_SECRETKEYBYTES ; 
 int crypto_kx_SEEDBYTES ; 
 int crypto_kx_SESSIONKEYBYTES ; 
 scalar_t__ crypto_kx_client_session_keys (unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_kx_keypair (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_kx_primitive () ; 
 int crypto_kx_publickeybytes () ; 
 int crypto_kx_secretkeybytes () ; 
 int /*<<< orphan*/  crypto_kx_seed_keypair (unsigned char*,unsigned char*,unsigned char*) ; 
 int crypto_kx_seedbytes () ; 
 scalar_t__ crypto_kx_server_session_keys (unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int crypto_kx_sessionkeybytes () ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,int) ; 
 unsigned char* small_order_p ; 
 int /*<<< orphan*/  sodium_bin2hex (char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 int /*<<< orphan*/  sodium_increment (unsigned char*,int) ; 
 scalar_t__ sodium_malloc (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tv_kx(void)
{
    unsigned char *seed;
    unsigned char *client_pk, *client_sk;
    unsigned char *client_rx, *client_tx;
    unsigned char *server_pk, *server_sk;
    unsigned char *server_rx, *server_tx;
    char           hex[65];
    int            i;

    seed = (unsigned char *) sodium_malloc(crypto_kx_SEEDBYTES);
    for (i = 0; i < crypto_kx_SEEDBYTES; i++) {
        seed[i] = (unsigned char) i;
    }
    client_pk = (unsigned char *) sodium_malloc(crypto_kx_PUBLICKEYBYTES);
    client_sk = (unsigned char *) sodium_malloc(crypto_kx_SECRETKEYBYTES);
    crypto_kx_seed_keypair(client_pk, client_sk, seed);

    sodium_bin2hex(hex, sizeof hex, client_pk, crypto_kx_PUBLICKEYBYTES);
    printf("client_pk: [%s]\n", hex);
    sodium_bin2hex(hex, sizeof hex, client_sk, crypto_kx_SECRETKEYBYTES);
    printf("client_sk: [%s]\n", hex);

    server_pk = (unsigned char *) sodium_malloc(crypto_kx_PUBLICKEYBYTES);
    server_sk = (unsigned char *) sodium_malloc(crypto_kx_SECRETKEYBYTES);
    crypto_kx_keypair(server_pk, server_sk);

    client_rx = (unsigned char *) sodium_malloc(crypto_kx_SESSIONKEYBYTES);
    client_tx = (unsigned char *) sodium_malloc(crypto_kx_SESSIONKEYBYTES);

    assert(crypto_kx_client_session_keys(client_rx, client_tx,
                                         client_pk, client_sk,
                                         small_order_p) == -1);
    if (crypto_kx_client_session_keys(client_rx, client_tx,
                                      client_pk, client_sk, server_pk) != 0) {
        printf("crypto_kx_client_session_keys() failed\n");
    }

    server_rx = (unsigned char *) sodium_malloc(crypto_kx_SESSIONKEYBYTES);
    server_tx = (unsigned char *) sodium_malloc(crypto_kx_SESSIONKEYBYTES);

    assert(crypto_kx_server_session_keys(server_rx, server_tx,
                                         server_pk, server_sk,
                                         small_order_p) == -1);
    if (crypto_kx_server_session_keys(server_rx, server_tx,
                                      server_pk, server_sk, client_pk) != 0) {
        printf("crypto_kx_server_session_keys() failed\n");
    }
    if (memcmp(server_rx, client_tx, crypto_kx_SESSIONKEYBYTES) != 0 ||
        memcmp(server_tx, client_rx, crypto_kx_SESSIONKEYBYTES) != 0) {
        printf("client session keys != server session keys\n");
    }

    sodium_increment(client_pk, crypto_kx_PUBLICKEYBYTES);
    if (crypto_kx_server_session_keys(server_rx, server_tx,
                                      server_pk, server_sk, client_pk) != 0) {
        printf("crypto_kx_server_session_keys() failed\n");
    }
    if (memcmp(server_rx, client_tx, crypto_kx_SESSIONKEYBYTES) == 0 &&
        memcmp(server_tx, client_rx, crypto_kx_SESSIONKEYBYTES) == 0) {
        printf("peer's public key is ignored\n");
    }

    crypto_kx_keypair(client_pk, client_sk);
    if (crypto_kx_server_session_keys(server_rx, server_tx,
                                      server_pk, server_sk, client_pk) != 0) {
        printf("crypto_kx_server_session_keys() failed\n");
    }
    if (memcmp(server_rx, client_tx, crypto_kx_SESSIONKEYBYTES) == 0 ||
        memcmp(server_tx, client_rx, crypto_kx_SESSIONKEYBYTES) == 0) {
        printf("session keys are constant\n");
    }

    crypto_kx_seed_keypair(client_pk, client_sk, seed);
    sodium_increment(seed, crypto_kx_SEEDBYTES);
    crypto_kx_seed_keypair(server_pk, server_sk, seed);
    if (crypto_kx_server_session_keys(server_rx, server_tx,
                                      server_pk, server_sk, client_pk) != 0) {
        printf("crypto_kx_server_session_keys() failed\n");
    }
    sodium_bin2hex(hex, sizeof hex, server_rx, crypto_kx_SESSIONKEYBYTES);
    printf("server_rx: [%s]\n", hex);
    sodium_bin2hex(hex, sizeof hex, server_tx, crypto_kx_SESSIONKEYBYTES);
    printf("server_tx: [%s]\n", hex);

    if (crypto_kx_client_session_keys(client_rx, client_tx,
                                      client_pk, client_sk, server_pk) != 0) {
        printf("crypto_kx_client_session_keys() failed\n");
    }
    sodium_bin2hex(hex, sizeof hex, client_rx, crypto_kx_SESSIONKEYBYTES);
    printf("client_rx: [%s]\n", hex);
    sodium_bin2hex(hex, sizeof hex, client_tx, crypto_kx_SESSIONKEYBYTES);
    printf("client_tx: [%s]\n", hex);

    randombytes_buf(client_rx, crypto_kx_SESSIONKEYBYTES);
    randombytes_buf(client_tx, crypto_kx_SESSIONKEYBYTES);
    randombytes_buf(server_rx, crypto_kx_SESSIONKEYBYTES);
    randombytes_buf(server_tx, crypto_kx_SESSIONKEYBYTES);
    if (crypto_kx_client_session_keys(client_rx, NULL,
                                      client_pk, client_sk, server_pk) != 0 ||
        crypto_kx_client_session_keys(NULL, client_tx,
                                      client_pk, client_sk, server_pk) != 0 ||
        crypto_kx_server_session_keys(server_rx, NULL,
                                      server_pk, server_sk, client_pk) != 0 ||
        crypto_kx_server_session_keys(NULL, server_tx,
                                      server_pk, server_sk, client_pk) != 0) {
        printf("failure when one of the pointers happens to be NULL");
    }
    assert(memcmp(client_rx, client_tx, crypto_kx_SESSIONKEYBYTES) == 0);
    assert(memcmp(client_tx, server_rx, crypto_kx_SESSIONKEYBYTES) == 0);
    assert(memcmp(server_rx, server_tx, crypto_kx_SESSIONKEYBYTES) == 0);

    sodium_free(client_rx);
    sodium_free(client_tx);
    sodium_free(server_rx);
    sodium_free(server_tx);
    sodium_free(server_sk);
    sodium_free(server_pk);
    sodium_free(client_sk);
    sodium_free(client_pk);
    sodium_free(seed);

    assert(strcmp(crypto_kx_primitive(), crypto_kx_PRIMITIVE) == 0);
    assert(crypto_kx_publickeybytes() == crypto_kx_PUBLICKEYBYTES);
    assert(crypto_kx_secretkeybytes() == crypto_kx_SECRETKEYBYTES);
    assert(crypto_kx_seedbytes() == crypto_kx_SEEDBYTES);
    assert(crypto_kx_sessionkeybytes() == crypto_kx_SESSIONKEYBYTES);

    printf("tv_kx: ok\n");
}