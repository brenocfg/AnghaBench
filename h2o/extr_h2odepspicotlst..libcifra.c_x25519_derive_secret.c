#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ ptls_iovec_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  X25519_KEY_SIZE ; 
 int /*<<< orphan*/  cf_curve25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25519_derive_secret(ptls_iovec_t *secret, const uint8_t *clientpriv, const uint8_t *clientpub,
                                const uint8_t *serverpriv, const uint8_t *serverpub)
{
    if ((secret->base = malloc(X25519_KEY_SIZE)) == NULL)
        return PTLS_ERROR_NO_MEMORY;

    cf_curve25519_mul(secret->base, clientpriv != NULL ? clientpriv : serverpriv, clientpriv != NULL ? serverpub : clientpub);
    secret->len = X25519_KEY_SIZE;
    return 0;
}