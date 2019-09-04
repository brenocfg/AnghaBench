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
 scalar_t__ crypto_core_ed25519_BYTES ; 
 scalar_t__ crypto_core_ed25519_NONREDUCEDSCALARBYTES ; 
 scalar_t__ crypto_core_ed25519_SCALARBYTES ; 
 int crypto_core_ed25519_UNIFORMBYTES ; 
 scalar_t__ crypto_core_ristretto255_BYTES ; 
 scalar_t__ crypto_core_ristretto255_HASHBYTES ; 
 scalar_t__ crypto_core_ristretto255_NONREDUCEDSCALARBYTES ; 
 scalar_t__ crypto_core_ristretto255_SCALARBYTES ; 
 scalar_t__ crypto_core_ristretto255_bytes () ; 
 scalar_t__ crypto_core_ristretto255_hashbytes () ; 
 scalar_t__ crypto_core_ristretto255_nonreducedscalarbytes () ; 
 scalar_t__ crypto_core_ristretto255_scalarbytes () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tv1 () ; 
 int /*<<< orphan*/  tv2 () ; 
 int /*<<< orphan*/  tv3 () ; 
 int /*<<< orphan*/  tv4 () ; 

int
main(void)
{
    tv1();
    tv2();
    tv3();
    tv4();

    assert(crypto_core_ristretto255_BYTES == crypto_core_ristretto255_bytes());
    assert(crypto_core_ristretto255_SCALARBYTES == crypto_core_ristretto255_scalarbytes());
    assert(crypto_core_ristretto255_NONREDUCEDSCALARBYTES == crypto_core_ristretto255_nonreducedscalarbytes());
    assert(crypto_core_ristretto255_NONREDUCEDSCALARBYTES >= crypto_core_ristretto255_SCALARBYTES);
    assert(crypto_core_ristretto255_HASHBYTES == crypto_core_ristretto255_hashbytes());
    assert(crypto_core_ristretto255_HASHBYTES >= crypto_core_ristretto255_BYTES);
    assert(crypto_core_ristretto255_BYTES == crypto_core_ed25519_BYTES);
    assert(crypto_core_ristretto255_SCALARBYTES == crypto_core_ed25519_SCALARBYTES);
    assert(crypto_core_ristretto255_NONREDUCEDSCALARBYTES == crypto_core_ed25519_NONREDUCEDSCALARBYTES);
    assert(crypto_core_ristretto255_HASHBYTES >= 2 * crypto_core_ed25519_UNIFORMBYTES);

    printf("OK\n");

    return 0;
}