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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_algorithm_t ;
struct TYPE_6__ {scalar_t__ len; scalar_t__* base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  priv ;

/* Variables and functions */
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int SECP256R1_PRIVATE_KEY_SIZE ; 
 scalar_t__ SECP256R1_PUBLIC_KEY_SIZE ; 
 scalar_t__ SECP256R1_SHARED_SECRET_SIZE ; 
 scalar_t__ TYPE_UNCOMPRESSED_PUBLIC_KEY ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  ptls_clear_memory (scalar_t__*,int) ; 
 TYPE_1__ ptls_iovec_init (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  uECC_make_key (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uECC_secp256r1 () ; 
 int /*<<< orphan*/  uECC_shared_secret (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int secp256r1_key_exchange(ptls_key_exchange_algorithm_t *algo, ptls_iovec_t *pubkey, ptls_iovec_t *secret,
                                  ptls_iovec_t peerkey)
{
    uint8_t priv[SECP256R1_PRIVATE_KEY_SIZE], *pub = NULL, *secbytes = NULL;
    int ret;

    if (peerkey.len != SECP256R1_PUBLIC_KEY_SIZE || peerkey.base[0] != TYPE_UNCOMPRESSED_PUBLIC_KEY) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    if ((pub = malloc(SECP256R1_PUBLIC_KEY_SIZE)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    if ((secbytes = malloc(SECP256R1_SHARED_SECRET_SIZE)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }

    pub[0] = TYPE_UNCOMPRESSED_PUBLIC_KEY;
    uECC_make_key(pub + 1, priv, uECC_secp256r1());
    if (!uECC_shared_secret(peerkey.base + 1, priv, secbytes, uECC_secp256r1())) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    *pubkey = ptls_iovec_init(pub, SECP256R1_PUBLIC_KEY_SIZE);
    *secret = ptls_iovec_init(secbytes, SECP256R1_SHARED_SECRET_SIZE);
    ret = 0;

Exit:
    ptls_clear_memory(priv, sizeof(priv));
    if (ret != 0) {
        free(secbytes);
        free(pub);
    }
    return ret;
}