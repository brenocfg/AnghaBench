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
 int /*<<< orphan*/  alicesk ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bobsk ; 
 int crypto_scalarmult (unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  crypto_scalarmult_BYTES ; 
 int /*<<< orphan*/  crypto_scalarmult_base (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned int crypto_scalarmult_bytes () ; 
 unsigned int crypto_scalarmult_curve25519_bytes () ; 
 unsigned int crypto_scalarmult_curve25519_scalarbytes () ; 
 int /*<<< orphan*/  crypto_scalarmult_primitive () ; 
 unsigned int crypto_scalarmult_scalarbytes () ; 
 char* hex ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 unsigned char* small_order_p ; 
 int /*<<< orphan*/  sodium_bin2hex (char*,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{
    unsigned char *alicepk =
        (unsigned char *) sodium_malloc(crypto_scalarmult_BYTES);
    unsigned char *bobpk =
        (unsigned char *) sodium_malloc(crypto_scalarmult_BYTES);
    unsigned char *k = (unsigned char *) sodium_malloc(crypto_scalarmult_BYTES);
    int            ret;

    assert(alicepk != NULL && bobpk != NULL && k != NULL);

    crypto_scalarmult_base(alicepk, alicesk);
    sodium_bin2hex(hex, sizeof hex, alicepk, crypto_scalarmult_BYTES);
    printf("%s\n", hex);

    crypto_scalarmult_base(bobpk, bobsk);
    sodium_bin2hex(hex, sizeof hex, bobpk, crypto_scalarmult_BYTES);
    printf("%s\n", hex);

    ret = crypto_scalarmult(k, alicesk, bobpk);
    assert(ret == 0);
    sodium_bin2hex(hex, sizeof hex, k, crypto_scalarmult_BYTES);
    printf("%s\n", hex);

    ret = crypto_scalarmult(k, bobsk, alicepk);
    assert(ret == 0);
    sodium_bin2hex(hex, sizeof hex, k, crypto_scalarmult_BYTES);
    printf("%s\n", hex);

    ret = crypto_scalarmult(k, bobsk, small_order_p);
    assert(ret == -1);

    sodium_free(bobpk);
    sodium_free(alicepk);
    sodium_free(k);

    assert(crypto_scalarmult_bytes() > 0U);
    assert(crypto_scalarmult_scalarbytes() > 0U);
    assert(strcmp(crypto_scalarmult_primitive(), "curve25519") == 0);
    assert(crypto_scalarmult_bytes() == crypto_scalarmult_curve25519_bytes());
    assert(crypto_scalarmult_scalarbytes() ==
           crypto_scalarmult_curve25519_scalarbytes());
    assert(crypto_scalarmult_bytes() == crypto_scalarmult_scalarbytes());

    return 0;
}