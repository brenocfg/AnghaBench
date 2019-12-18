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
typedef  int /*<<< orphan*/  uint8_t ;
struct st_ptls_traffic_protection_t {int /*<<< orphan*/  seq; int /*<<< orphan*/  aead; } ;
typedef  int /*<<< orphan*/  aad ;

/* Variables and functions */
 int PTLS_ALERT_BAD_RECORD_MAC ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  build_aad (int /*<<< orphan*/ *,size_t) ; 
 size_t ptls_aead_decrypt (int /*<<< orphan*/ ,void*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int aead_decrypt(struct st_ptls_traffic_protection_t *ctx, void *output, size_t *outlen, const void *input, size_t inlen)
{
    uint8_t aad[5];

    build_aad(aad, inlen);
    if ((*outlen = ptls_aead_decrypt(ctx->aead, output, input, inlen, ctx->seq, aad, sizeof(aad))) == SIZE_MAX)
        return PTLS_ALERT_BAD_RECORD_MAC;
    ++ctx->seq;
    return 0;
}