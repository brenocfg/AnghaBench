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
 int WNAF_BITS ; 
 int WNAF_SIZE (int) ; 
 int secp256k1_scalar_get_bits_var (int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ secp256k1_scalar_is_even (int /*<<< orphan*/  const*) ; 
 scalar_t__ secp256k1_scalar_is_zero (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int secp256k1_wnaf_fixed(int *wnaf, const secp256k1_scalar *s, int w) {
    int skew = 0;
    int pos;
    int max_pos;
    int last_w;
    const secp256k1_scalar *work = s;

    if (secp256k1_scalar_is_zero(s)) {
        for (pos = 0; pos < WNAF_SIZE(w); pos++) {
            wnaf[pos] = 0;
        }
        return 0;
    }

    if (secp256k1_scalar_is_even(s)) {
        skew = 1;
    }

    wnaf[0] = secp256k1_scalar_get_bits_var(work, 0, w) + skew;
    /* Compute last window size. Relevant when window size doesn't divide the
     * number of bits in the scalar */
    last_w = WNAF_BITS - (WNAF_SIZE(w) - 1) * w;

    /* Store the position of the first nonzero word in max_pos to allow
     * skipping leading zeros when calculating the wnaf. */
    for (pos = WNAF_SIZE(w) - 1; pos > 0; pos--) {
        int val = secp256k1_scalar_get_bits_var(work, pos * w, pos == WNAF_SIZE(w)-1 ? last_w : w);
        if(val != 0) {
            break;
        }
        wnaf[pos] = 0;
    }
    max_pos = pos;
    pos = 1;

    while (pos <= max_pos) {
        int val = secp256k1_scalar_get_bits_var(work, pos * w, pos == WNAF_SIZE(w)-1 ? last_w : w);
        if ((val & 1) == 0) {
            wnaf[pos - 1] -= (1 << w);
            wnaf[pos] = (val + 1);
        } else {
            wnaf[pos] = val;
        }
        /* Set a coefficient to zero if it is 1 or -1 and the proceeding digit
         * is strictly negative or strictly positive respectively. Only change
         * coefficients at previous positions because above code assumes that
         * wnaf[pos - 1] is odd.
         */
        if (pos >= 2 && ((wnaf[pos - 1] == 1 && wnaf[pos - 2] < 0) || (wnaf[pos - 1] == -1 && wnaf[pos - 2] > 0))) {
            if (wnaf[pos - 1] == 1) {
                wnaf[pos - 2] += 1 << w;
            } else {
                wnaf[pos - 2] -= 1 << w;
            }
            wnaf[pos - 1] = 0;
        }
        ++pos;
    }

    return skew;
}