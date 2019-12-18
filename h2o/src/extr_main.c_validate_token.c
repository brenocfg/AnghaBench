#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct sockaddr {int dummy; } ;
struct TYPE_13__ {scalar_t__ cidpair_hash; } ;
struct TYPE_12__ {int /*<<< orphan*/  sa; } ;
struct TYPE_14__ {scalar_t__ issued_at; TYPE_4__ retry; scalar_t__ is_retry; TYPE_3__ remote; } ;
typedef  TYPE_5__ quicly_address_token_plaintext_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_1__* quic; } ;
struct TYPE_15__ {TYPE_2__ super; } ;
typedef  TYPE_6__ h2o_http3_server_ctx_t ;
struct TYPE_16__ {scalar_t__ (* cb ) (TYPE_9__*) ;} ;
struct TYPE_10__ {TYPE_9__* now; } ;

/* Variables and functions */
 scalar_t__ h2o_socket_compare_address (struct sockaddr*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ptls_openssl_sha256 ; 
 scalar_t__ quicly_retry_calc_cidpair_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub1 (TYPE_9__*) ; 

__attribute__((used)) static int validate_token(h2o_http3_server_ctx_t *ctx, struct sockaddr *remote, ptls_iovec_t client_cid, ptls_iovec_t server_cid,
                          quicly_address_token_plaintext_t *token)
{
    int64_t age;

    if ((age = ctx->super.quic->now->cb(ctx->super.quic->now) - token->issued_at) < 0)
        age = 0;
    if (h2o_socket_compare_address(remote, &token->remote.sa, token->is_retry) != 0)
        return 0;
    if (token->is_retry) {
        if (age > 30 * 1000)
            return 0;
        uint64_t cidhash_actual;
        if (quicly_retry_calc_cidpair_hash(&ptls_openssl_sha256, client_cid, server_cid, &cidhash_actual) != 0)
            return 0;
        if (token->retry.cidpair_hash != cidhash_actual)
            return 0;
    } else {
        if (age > 10 * 60 * 1000)
            return 0;
    }

    return 1;
}