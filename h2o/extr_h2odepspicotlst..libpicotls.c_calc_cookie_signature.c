#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_39__ {int* client_random; int* server_name; TYPE_3__* cipher_suite; TYPE_2__* ctx; } ;
typedef  TYPE_7__ ptls_t ;
struct TYPE_40__ {int id; } ;
typedef  TYPE_8__ ptls_key_exchange_algorithm_t ;
struct TYPE_41__ {size_t len; int* base; } ;
typedef  TYPE_9__ ptls_iovec_t ;
struct TYPE_30__ {int /*<<< orphan*/  (* final ) (TYPE_10__*,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update ) (TYPE_10__*,int*,size_t) ;} ;
typedef  TYPE_10__ ptls_hash_context_t ;
struct TYPE_31__ {int /*<<< orphan*/  digest_size; } ;
typedef  TYPE_11__ ptls_hash_algorithm_t ;
struct TYPE_36__ {size_t len; int* base; } ;
struct TYPE_37__ {TYPE_4__ additional_data; int /*<<< orphan*/  key; } ;
struct TYPE_38__ {TYPE_5__ cookie; } ;
struct TYPE_32__ {TYPE_6__ server; } ;
typedef  TYPE_12__ ptls_handshake_properties_t ;
struct TYPE_35__ {int id; } ;
struct TYPE_34__ {TYPE_1__** cipher_suites; } ;
struct TYPE_33__ {TYPE_11__* hash; } ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_FREE ; 
 size_t UINT8_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_10__* ptls_hmac_create (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  stub10 (TYPE_10__*,int*,size_t) ; 
 int /*<<< orphan*/  stub11 (TYPE_10__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*,int*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*,int*,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_10__*,int*,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_10__*,int*,size_t) ; 
 int /*<<< orphan*/  stub9 (TYPE_10__*,int*,int) ; 

__attribute__((used)) static int calc_cookie_signature(ptls_t *tls, ptls_handshake_properties_t *properties,
                                 ptls_key_exchange_algorithm_t *negotiated_group, ptls_iovec_t tbs, uint8_t *sig)
{
    ptls_hash_algorithm_t *algo = tls->ctx->cipher_suites[0]->hash;
    ptls_hash_context_t *hctx;

    if ((hctx = ptls_hmac_create(algo, properties->server.cookie.key, algo->digest_size)) == NULL)
        return PTLS_ERROR_NO_MEMORY;

#define UPDATE_BLOCK(p, _len)                                                                                                      \
    do {                                                                                                                           \
        size_t len = (_len);                                                                                                       \
        assert(len < UINT8_MAX);                                                                                                   \
        uint8_t len8 = (uint8_t)len;                                                                                               \
        hctx->update(hctx, &len8, 1);                                                                                              \
        hctx->update(hctx, (p), len);                                                                                              \
    } while (0)
#define UPDATE16(_v)                                                                                                               \
    do {                                                                                                                           \
        uint16_t v = (_v);                                                                                                         \
        uint8_t b[2] = {v >> 8, v & 0xff};                                                                                         \
        hctx->update(hctx, b, 2);                                                                                                  \
    } while (0)

    UPDATE_BLOCK(tls->client_random, sizeof(tls->client_random));
    UPDATE_BLOCK(tls->server_name, tls->server_name != NULL ? strlen(tls->server_name) : 0);
    UPDATE16(tls->cipher_suite->id);
    UPDATE16(negotiated_group->id);
    UPDATE_BLOCK(properties->server.cookie.additional_data.base, properties->server.cookie.additional_data.len);

    UPDATE_BLOCK(tbs.base, tbs.len);

#undef UPDATE_BLOCK
#undef UPDATE16

    hctx->final(hctx, sig, PTLS_HASH_FINAL_MODE_FREE);
    return 0;
}