#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_quicly_cipher_context_t {int /*<<< orphan*/  aead; int /*<<< orphan*/  header_protection; } ;
struct TYPE_5__ {TYPE_3__* hash; int /*<<< orphan*/  aead; } ;
typedef  TYPE_1__ ptls_cipher_suite_t ;
typedef  int /*<<< orphan*/  aead_secret ;
struct TYPE_6__ {int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int ptls_hkdf_expand_label (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_iovec_init (void const*,int /*<<< orphan*/ ) ; 
 int setup_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_initial_key(struct st_quicly_cipher_context_t *ctx, ptls_cipher_suite_t *cs, const void *master_secret,
                             const char *label, int is_enc)
{
    uint8_t aead_secret[PTLS_MAX_DIGEST_SIZE];
    int ret;

    if ((ret = ptls_hkdf_expand_label(cs->hash, aead_secret, cs->hash->digest_size,
                                      ptls_iovec_init(master_secret, cs->hash->digest_size), label, ptls_iovec_init(NULL, 0),
                                      NULL)) != 0)
        goto Exit;
    if ((ret = setup_cipher(&ctx->header_protection, &ctx->aead, cs->aead, cs->hash, is_enc, aead_secret)) != 0)
        goto Exit;

Exit:
    ptls_clear_memory(aead_secret, sizeof(aead_secret));
    return ret;
}