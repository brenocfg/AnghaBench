#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_algorithm_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  priv ;

/* Variables and functions */
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int X25519_KEY_SIZE ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ ptls_iovec_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x25519_create_keypair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int x25519_derive_secret (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x25519_key_exchange(ptls_key_exchange_algorithm_t *algo, ptls_iovec_t *pubkey, ptls_iovec_t *secret,
                               ptls_iovec_t peerkey)
{
    uint8_t priv[X25519_KEY_SIZE], *pub = NULL;
    int ret;

    if (peerkey.len != X25519_KEY_SIZE) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    if ((pub = malloc(X25519_KEY_SIZE)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }

    x25519_create_keypair(priv, pub);
    if ((ret = x25519_derive_secret(secret, NULL, peerkey.base, priv, pub)) != 0)
        goto Exit;

    *pubkey = ptls_iovec_init(pub, X25519_KEY_SIZE);
    ret = 0;

Exit:
    ptls_clear_memory(priv, sizeof(priv));
    if (pub != NULL && ret != 0)
        ptls_clear_memory(pub, X25519_KEY_SIZE);
    return ret;
}