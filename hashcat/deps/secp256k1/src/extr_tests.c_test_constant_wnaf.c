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
typedef  int /*<<< orphan*/  secp256k1_scalar ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int WNAF_SIZE_BITS (int,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_cadd_bit (int /*<<< orphan*/ *,int,int) ; 
 int secp256k1_scalar_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_scalar_shr_int (int /*<<< orphan*/ *,int) ; 
 int secp256k1_wnaf_const (int*,int /*<<< orphan*/ *,int,int) ; 

void test_constant_wnaf(const secp256k1_scalar *number, int w) {
    secp256k1_scalar x, shift;
    int wnaf[256] = {0};
    int i;
    int skew;
    int bits = 256;
    secp256k1_scalar num = *number;

    secp256k1_scalar_set_int(&x, 0);
    secp256k1_scalar_set_int(&shift, 1 << w);
    /* With USE_ENDOMORPHISM on we only consider 128-bit numbers */
#ifdef USE_ENDOMORPHISM
    for (i = 0; i < 16; ++i) {
        secp256k1_scalar_shr_int(&num, 8);
    }
    bits = 128;
#endif
    skew = secp256k1_wnaf_const(wnaf, &num, w, bits);

    for (i = WNAF_SIZE_BITS(bits, w); i >= 0; --i) {
        secp256k1_scalar t;
        int v = wnaf[i];
        CHECK(v != 0); /* check nonzero */
        CHECK(v & 1);  /* check parity */
        CHECK(v > -(1 << w)); /* check range above */
        CHECK(v < (1 << w));  /* check range below */

        secp256k1_scalar_mul(&x, &x, &shift);
        if (v >= 0) {
            secp256k1_scalar_set_int(&t, v);
        } else {
            secp256k1_scalar_set_int(&t, -v);
            secp256k1_scalar_negate(&t, &t);
        }
        secp256k1_scalar_add(&x, &x, &t);
    }
    /* Skew num because when encoding numbers as odd we use an offset */
    secp256k1_scalar_cadd_bit(&num, skew == 2, 1);
    CHECK(secp256k1_scalar_eq(&x, &num));
}