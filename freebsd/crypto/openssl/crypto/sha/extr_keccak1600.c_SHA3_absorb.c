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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  A ;

/* Variables and functions */
 int BitInterleave (int) ; 
 int /*<<< orphan*/  KeccakF1600 (int**) ; 
 int /*<<< orphan*/  assert (int) ; 

size_t SHA3_absorb(uint64_t A[5][5], const unsigned char *inp, size_t len,
                   size_t r)
{
    uint64_t *A_flat = (uint64_t *)A;
    size_t i, w = r / 8;

    assert(r < (25 * sizeof(A[0][0])) && (r % 8) == 0);

    while (len >= r) {
        for (i = 0; i < w; i++) {
            uint64_t Ai = (uint64_t)inp[0]       | (uint64_t)inp[1] << 8  |
                          (uint64_t)inp[2] << 16 | (uint64_t)inp[3] << 24 |
                          (uint64_t)inp[4] << 32 | (uint64_t)inp[5] << 40 |
                          (uint64_t)inp[6] << 48 | (uint64_t)inp[7] << 56;
            inp += 8;

            A_flat[i] ^= BitInterleave(Ai);
        }
        KeccakF1600(A);
        len -= r;
    }

    return len;
}