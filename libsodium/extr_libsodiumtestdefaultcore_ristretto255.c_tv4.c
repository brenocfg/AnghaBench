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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_NONREDUCEDSCALARBYTES ; 
 int /*<<< orphan*/  crypto_core_ristretto255_SCALARBYTES ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_add (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_complement (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_invert (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_mul (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_negate (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_random (unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_reduce (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_core_ristretto255_scalar_sub (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 int /*<<< orphan*/  sodium_is_zero (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sodium_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tv4(void)
{
    unsigned char *r;
    unsigned char *s1;
    unsigned char *s2;
    unsigned char *s3;
    unsigned char *s4;

    r = (unsigned char *) sodium_malloc(crypto_core_ristretto255_NONREDUCEDSCALARBYTES);
    s1 = (unsigned char *) sodium_malloc(crypto_core_ristretto255_SCALARBYTES);
    s2 = (unsigned char *) sodium_malloc(crypto_core_ristretto255_SCALARBYTES);
    s3 = (unsigned char *) sodium_malloc(crypto_core_ristretto255_SCALARBYTES);
    s4 = (unsigned char *) sodium_malloc(crypto_core_ristretto255_SCALARBYTES);

    crypto_core_ristretto255_scalar_random(s1);
    randombytes_buf(r, crypto_core_ristretto255_NONREDUCEDSCALARBYTES);
    crypto_core_ristretto255_scalar_reduce(s2, r);
    memcpy(s4, s1, crypto_core_ristretto255_SCALARBYTES);
    crypto_core_ristretto255_scalar_add(s3, s1, s2);
    crypto_core_ristretto255_scalar_sub(s4, s1, s2);
    crypto_core_ristretto255_scalar_add(s2, s3, s4);
    crypto_core_ristretto255_scalar_sub(s2, s2, s1);
    crypto_core_ristretto255_scalar_mul(s2, s3, s2);
    crypto_core_ristretto255_scalar_invert(s4, s3);
    crypto_core_ristretto255_scalar_mul(s2, s2, s4);
    crypto_core_ristretto255_scalar_negate(s1, s1);
    crypto_core_ristretto255_scalar_add(s2, s2, s1);
    crypto_core_ristretto255_scalar_complement(s1, s2);
    s1[0]--;
    assert(sodium_is_zero(s1, crypto_core_ristretto255_SCALARBYTES));

    sodium_free(s1);
    sodium_free(s2);
    sodium_free(s3);
    sodium_free(s4);
    sodium_free(r);
}