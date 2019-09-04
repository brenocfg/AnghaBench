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
struct st_x9_62_keyex_context_t {int /*<<< orphan*/  privkey; int /*<<< orphan*/  bn_ctx; } ;
typedef  int /*<<< orphan*/  ptls_key_exchange_context_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int PTLS_ALERT_DECODE_ERROR ; 
 int ecdh_calc_secret (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * x9_62_decode_point (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x9_62_free_context (struct st_x9_62_keyex_context_t*) ; 

__attribute__((used)) static int x9_62_on_exchange(ptls_key_exchange_context_t **_ctx, int release, ptls_iovec_t *secret, ptls_iovec_t peerkey)
{
    struct st_x9_62_keyex_context_t *ctx = (struct st_x9_62_keyex_context_t *)*_ctx;
    const EC_GROUP *group = EC_KEY_get0_group(ctx->privkey);
    EC_POINT *peer_point = NULL;
    int ret;

    if (secret == NULL) {
        ret = 0;
        goto Exit;
    }

    if ((peer_point = x9_62_decode_point(group, peerkey, ctx->bn_ctx)) == NULL) {
        ret = PTLS_ALERT_DECODE_ERROR;
        goto Exit;
    }
    if ((ret = ecdh_calc_secret(secret, group, ctx->privkey, peer_point)) != 0)
        goto Exit;

Exit:
    if (peer_point != NULL)
        EC_POINT_free(peer_point);
    if (release) {
        x9_62_free_context(ctx);
        *_ctx = NULL;
    }
    return ret;
}