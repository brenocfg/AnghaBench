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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/ * KEY_TABLE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Camellia_Feistel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GETU32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RotLeft128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGMA ; 

int Camellia_Ekeygen(int keyBitLength, const u8 *rawKey, KEY_TABLE_TYPE k)
{
    register u32 s0, s1, s2, s3;

    k[0] = s0 = GETU32(rawKey);
    k[1] = s1 = GETU32(rawKey + 4);
    k[2] = s2 = GETU32(rawKey + 8);
    k[3] = s3 = GETU32(rawKey + 12);

    if (keyBitLength != 128) {
        k[8] = s0 = GETU32(rawKey + 16);
        k[9] = s1 = GETU32(rawKey + 20);
        if (keyBitLength == 192) {
            k[10] = s2 = ~s0;
            k[11] = s3 = ~s1;
        } else {
            k[10] = s2 = GETU32(rawKey + 24);
            k[11] = s3 = GETU32(rawKey + 28);
        }
        s0 ^= k[0], s1 ^= k[1], s2 ^= k[2], s3 ^= k[3];
    }

    /* Use the Feistel routine to scramble the key material */
    Camellia_Feistel(s0, s1, s2, s3, SIGMA + 0);
    Camellia_Feistel(s2, s3, s0, s1, SIGMA + 2);

    s0 ^= k[0], s1 ^= k[1], s2 ^= k[2], s3 ^= k[3];
    Camellia_Feistel(s0, s1, s2, s3, SIGMA + 4);
    Camellia_Feistel(s2, s3, s0, s1, SIGMA + 6);

    /* Fill the keyTable. Requires many block rotations. */
    if (keyBitLength == 128) {
        k[4] = s0, k[5] = s1, k[6] = s2, k[7] = s3;
        RotLeft128(s0, s1, s2, s3, 15); /* KA <<< 15 */
        k[12] = s0, k[13] = s1, k[14] = s2, k[15] = s3;
        RotLeft128(s0, s1, s2, s3, 15); /* KA <<< 30 */
        k[16] = s0, k[17] = s1, k[18] = s2, k[19] = s3;
        RotLeft128(s0, s1, s2, s3, 15); /* KA <<< 45 */
        k[24] = s0, k[25] = s1;
        RotLeft128(s0, s1, s2, s3, 15); /* KA <<< 60 */
        k[28] = s0, k[29] = s1, k[30] = s2, k[31] = s3;
        RotLeft128(s1, s2, s3, s0, 2); /* KA <<< 94 */
        k[40] = s1, k[41] = s2, k[42] = s3, k[43] = s0;
        RotLeft128(s1, s2, s3, s0, 17); /* KA <<<111 */
        k[48] = s1, k[49] = s2, k[50] = s3, k[51] = s0;

        s0 = k[0], s1 = k[1], s2 = k[2], s3 = k[3];
        RotLeft128(s0, s1, s2, s3, 15); /* KL <<< 15 */
        k[8] = s0, k[9] = s1, k[10] = s2, k[11] = s3;
        RotLeft128(s0, s1, s2, s3, 30); /* KL <<< 45 */
        k[20] = s0, k[21] = s1, k[22] = s2, k[23] = s3;
        RotLeft128(s0, s1, s2, s3, 15); /* KL <<< 60 */
        k[26] = s2, k[27] = s3;
        RotLeft128(s0, s1, s2, s3, 17); /* KL <<< 77 */
        k[32] = s0, k[33] = s1, k[34] = s2, k[35] = s3;
        RotLeft128(s0, s1, s2, s3, 17); /* KL <<< 94 */
        k[36] = s0, k[37] = s1, k[38] = s2, k[39] = s3;
        RotLeft128(s0, s1, s2, s3, 17); /* KL <<<111 */
        k[44] = s0, k[45] = s1, k[46] = s2, k[47] = s3;

        return 3;               /* grand rounds */
    } else {
        k[12] = s0, k[13] = s1, k[14] = s2, k[15] = s3;
        s0 ^= k[8], s1 ^= k[9], s2 ^= k[10], s3 ^= k[11];
        Camellia_Feistel(s0, s1, s2, s3, (SIGMA + 8));
        Camellia_Feistel(s2, s3, s0, s1, (SIGMA + 10));

        k[4] = s0, k[5] = s1, k[6] = s2, k[7] = s3;
        RotLeft128(s0, s1, s2, s3, 30); /* KB <<< 30 */
        k[20] = s0, k[21] = s1, k[22] = s2, k[23] = s3;
        RotLeft128(s0, s1, s2, s3, 30); /* KB <<< 60 */
        k[40] = s0, k[41] = s1, k[42] = s2, k[43] = s3;
        RotLeft128(s1, s2, s3, s0, 19); /* KB <<<111 */
        k[64] = s1, k[65] = s2, k[66] = s3, k[67] = s0;

        s0 = k[8], s1 = k[9], s2 = k[10], s3 = k[11];
        RotLeft128(s0, s1, s2, s3, 15); /* KR <<< 15 */
        k[8] = s0, k[9] = s1, k[10] = s2, k[11] = s3;
        RotLeft128(s0, s1, s2, s3, 15); /* KR <<< 30 */
        k[16] = s0, k[17] = s1, k[18] = s2, k[19] = s3;
        RotLeft128(s0, s1, s2, s3, 30); /* KR <<< 60 */
        k[36] = s0, k[37] = s1, k[38] = s2, k[39] = s3;
        RotLeft128(s1, s2, s3, s0, 2); /* KR <<< 94 */
        k[52] = s1, k[53] = s2, k[54] = s3, k[55] = s0;

        s0 = k[12], s1 = k[13], s2 = k[14], s3 = k[15];
        RotLeft128(s0, s1, s2, s3, 15); /* KA <<< 15 */
        k[12] = s0, k[13] = s1, k[14] = s2, k[15] = s3;
        RotLeft128(s0, s1, s2, s3, 30); /* KA <<< 45 */
        k[28] = s0, k[29] = s1, k[30] = s2, k[31] = s3;
        /* KA <<< 77 */
        k[48] = s1, k[49] = s2, k[50] = s3, k[51] = s0;
        RotLeft128(s1, s2, s3, s0, 17); /* KA <<< 94 */
        k[56] = s1, k[57] = s2, k[58] = s3, k[59] = s0;

        s0 = k[0], s1 = k[1], s2 = k[2], s3 = k[3];
        RotLeft128(s1, s2, s3, s0, 13); /* KL <<< 45 */
        k[24] = s1, k[25] = s2, k[26] = s3, k[27] = s0;
        RotLeft128(s1, s2, s3, s0, 15); /* KL <<< 60 */
        k[32] = s1, k[33] = s2, k[34] = s3, k[35] = s0;
        RotLeft128(s1, s2, s3, s0, 17); /* KL <<< 77 */
        k[44] = s1, k[45] = s2, k[46] = s3, k[47] = s0;
        RotLeft128(s2, s3, s0, s1, 2); /* KL <<<111 */
        k[60] = s2, k[61] = s3, k[62] = s0, k[63] = s1;

        return 4;               /* grand rounds */
    }
    /*
     * It is possible to perform certain precalculations, which
     * would spare few cycles in block procedure. It's not done,
     * because it upsets the performance balance between key
     * setup and block procedures, negatively affecting overall
     * throughput in applications operating on short messages
     * and volatile keys.
     */
}