#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_secp256r1_key_exhchange_t {int /*<<< orphan*/  priv; } ;
typedef  struct st_secp256r1_key_exhchange_t uint8_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_context_t ;
struct TYPE_5__ {scalar_t__ len; scalar_t__* base; } ;
typedef  TYPE_1__ ptls_iovec_t ;

/* Variables and functions */
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ERROR_NO_MEMORY ; 
 scalar_t__ SECP256R1_PUBLIC_KEY_SIZE ; 
 int /*<<< orphan*/  SECP256R1_SHARED_SECRET_SIZE ; 
 scalar_t__ TYPE_UNCOMPRESSED_PUBLIC_KEY ; 
 int /*<<< orphan*/  free (struct st_secp256r1_key_exhchange_t*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ ptls_iovec_init (struct st_secp256r1_key_exhchange_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uECC_secp256r1 () ; 
 int /*<<< orphan*/  uECC_shared_secret (scalar_t__*,int /*<<< orphan*/ ,struct st_secp256r1_key_exhchange_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int secp256r1_on_exchange(ptls_key_exchange_context_t **_ctx, int release, ptls_iovec_t *secret, ptls_iovec_t peerkey)
{
    struct st_secp256r1_key_exhchange_t *ctx = (struct st_secp256r1_key_exhchange_t *)*_ctx;
    uint8_t *secbytes = NULL;
    int ret;

    if (secret == NULL) {
        ret = 0;
        goto Exit;
    }

    if (peerkey.len != SECP256R1_PUBLIC_KEY_SIZE || peerkey.base[0] != TYPE_UNCOMPRESSED_PUBLIC_KEY) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    if ((secbytes = (uint8_t *)malloc(SECP256R1_SHARED_SECRET_SIZE)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    if (!uECC_shared_secret(peerkey.base + 1, ctx->priv, secbytes, uECC_secp256r1())) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    *secret = ptls_iovec_init(secbytes, SECP256R1_SHARED_SECRET_SIZE);
    ret = 0;

Exit:
    if (ret != 0)
        free(secbytes);
    if (release) {
        ptls_clear_memory(ctx->priv, sizeof(ctx->priv));
        free(ctx);
        *_ctx = NULL;
    }
    return ret;
}