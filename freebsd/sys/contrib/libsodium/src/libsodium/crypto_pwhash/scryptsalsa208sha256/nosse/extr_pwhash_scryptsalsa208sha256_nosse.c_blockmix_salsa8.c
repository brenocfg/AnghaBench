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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  escrypt_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  blkcpy_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkxor_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  salsa20_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
blockmix_salsa8(const uint32_t *Bin, uint32_t *Bout, uint32_t *X, size_t r)
{
    size_t i;

    /* 1: X <-- B_{2r - 1} */
    blkcpy_64((escrypt_block_t *) X,
              (escrypt_block_t *) &Bin[(2 * r - 1) * 16]);

    /* 2: for i = 0 to 2r - 1 do */
    for (i = 0; i < 2 * r; i += 2) {
        /* 3: X <-- H(X \xor B_i) */
        blkxor_64((escrypt_block_t *) X, (escrypt_block_t *) &Bin[i * 16]);
        salsa20_8(X);

        /* 4: Y_i <-- X */
        /* 6: B' <-- (Y_0, Y_2 ... Y_{2r-2}, Y_1, Y_3 ... Y_{2r-1}) */
        blkcpy_64((escrypt_block_t *) &Bout[i * 8], (escrypt_block_t *) X);

        /* 3: X <-- H(X \xor B_i) */
        blkxor_64((escrypt_block_t *) X, (escrypt_block_t *) &Bin[i * 16 + 16]);
        salsa20_8(X);

        /* 4: Y_i <-- X */
        /* 6: B' <-- (Y_0, Y_2 ... Y_{2r-2}, Y_1, Y_3 ... Y_{2r-1}) */
        blkcpy_64((escrypt_block_t *) &Bout[i * 8 + r * 16],
                  (escrypt_block_t *) X);
    }
}