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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct serpent_ctx {int /*<<< orphan*/ * expkey; } ;

/* Variables and functions */
 int SERPENT_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  __serpent_setkey_sbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyiter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int __serpent_setkey(struct serpent_ctx *ctx, const u8 *key,
		     unsigned int keylen)
{
	u32 *k = ctx->expkey;
	u8  *k8 = (u8 *)k;
	u32 r0, r1, r2, r3, r4;
	int i;

	/* Copy key, add padding */

	for (i = 0; i < keylen; ++i)
		k8[i] = key[i];
	if (i < SERPENT_MAX_KEY_SIZE)
		k8[i++] = 1;
	while (i < SERPENT_MAX_KEY_SIZE)
		k8[i++] = 0;

	/* Expand key using polynomial */

	r0 = le32_to_cpu(k[3]);
	r1 = le32_to_cpu(k[4]);
	r2 = le32_to_cpu(k[5]);
	r3 = le32_to_cpu(k[6]);
	r4 = le32_to_cpu(k[7]);

	keyiter(le32_to_cpu(k[0]), r0, r4, r2, 0, 0);
	keyiter(le32_to_cpu(k[1]), r1, r0, r3, 1, 1);
	keyiter(le32_to_cpu(k[2]), r2, r1, r4, 2, 2);
	keyiter(le32_to_cpu(k[3]), r3, r2, r0, 3, 3);
	keyiter(le32_to_cpu(k[4]), r4, r3, r1, 4, 4);
	keyiter(le32_to_cpu(k[5]), r0, r4, r2, 5, 5);
	keyiter(le32_to_cpu(k[6]), r1, r0, r3, 6, 6);
	keyiter(le32_to_cpu(k[7]), r2, r1, r4, 7, 7);

	keyiter(k[0], r3, r2, r0, 8, 8);
	keyiter(k[1], r4, r3, r1, 9, 9);
	keyiter(k[2], r0, r4, r2, 10, 10);
	keyiter(k[3], r1, r0, r3, 11, 11);
	keyiter(k[4], r2, r1, r4, 12, 12);
	keyiter(k[5], r3, r2, r0, 13, 13);
	keyiter(k[6], r4, r3, r1, 14, 14);
	keyiter(k[7], r0, r4, r2, 15, 15);
	keyiter(k[8], r1, r0, r3, 16, 16);
	keyiter(k[9], r2, r1, r4, 17, 17);
	keyiter(k[10], r3, r2, r0, 18, 18);
	keyiter(k[11], r4, r3, r1, 19, 19);
	keyiter(k[12], r0, r4, r2, 20, 20);
	keyiter(k[13], r1, r0, r3, 21, 21);
	keyiter(k[14], r2, r1, r4, 22, 22);
	keyiter(k[15], r3, r2, r0, 23, 23);
	keyiter(k[16], r4, r3, r1, 24, 24);
	keyiter(k[17], r0, r4, r2, 25, 25);
	keyiter(k[18], r1, r0, r3, 26, 26);
	keyiter(k[19], r2, r1, r4, 27, 27);
	keyiter(k[20], r3, r2, r0, 28, 28);
	keyiter(k[21], r4, r3, r1, 29, 29);
	keyiter(k[22], r0, r4, r2, 30, 30);
	keyiter(k[23], r1, r0, r3, 31, 31);

	k += 50;

	keyiter(k[-26], r2, r1, r4, 32, -18);
	keyiter(k[-25], r3, r2, r0, 33, -17);
	keyiter(k[-24], r4, r3, r1, 34, -16);
	keyiter(k[-23], r0, r4, r2, 35, -15);
	keyiter(k[-22], r1, r0, r3, 36, -14);
	keyiter(k[-21], r2, r1, r4, 37, -13);
	keyiter(k[-20], r3, r2, r0, 38, -12);
	keyiter(k[-19], r4, r3, r1, 39, -11);
	keyiter(k[-18], r0, r4, r2, 40, -10);
	keyiter(k[-17], r1, r0, r3, 41, -9);
	keyiter(k[-16], r2, r1, r4, 42, -8);
	keyiter(k[-15], r3, r2, r0, 43, -7);
	keyiter(k[-14], r4, r3, r1, 44, -6);
	keyiter(k[-13], r0, r4, r2, 45, -5);
	keyiter(k[-12], r1, r0, r3, 46, -4);
	keyiter(k[-11], r2, r1, r4, 47, -3);
	keyiter(k[-10], r3, r2, r0, 48, -2);
	keyiter(k[-9], r4, r3, r1, 49, -1);
	keyiter(k[-8], r0, r4, r2, 50, 0);
	keyiter(k[-7], r1, r0, r3, 51, 1);
	keyiter(k[-6], r2, r1, r4, 52, 2);
	keyiter(k[-5], r3, r2, r0, 53, 3);
	keyiter(k[-4], r4, r3, r1, 54, 4);
	keyiter(k[-3], r0, r4, r2, 55, 5);
	keyiter(k[-2], r1, r0, r3, 56, 6);
	keyiter(k[-1], r2, r1, r4, 57, 7);
	keyiter(k[0], r3, r2, r0, 58, 8);
	keyiter(k[1], r4, r3, r1, 59, 9);
	keyiter(k[2], r0, r4, r2, 60, 10);
	keyiter(k[3], r1, r0, r3, 61, 11);
	keyiter(k[4], r2, r1, r4, 62, 12);
	keyiter(k[5], r3, r2, r0, 63, 13);
	keyiter(k[6], r4, r3, r1, 64, 14);
	keyiter(k[7], r0, r4, r2, 65, 15);
	keyiter(k[8], r1, r0, r3, 66, 16);
	keyiter(k[9], r2, r1, r4, 67, 17);
	keyiter(k[10], r3, r2, r0, 68, 18);
	keyiter(k[11], r4, r3, r1, 69, 19);
	keyiter(k[12], r0, r4, r2, 70, 20);
	keyiter(k[13], r1, r0, r3, 71, 21);
	keyiter(k[14], r2, r1, r4, 72, 22);
	keyiter(k[15], r3, r2, r0, 73, 23);
	keyiter(k[16], r4, r3, r1, 74, 24);
	keyiter(k[17], r0, r4, r2, 75, 25);
	keyiter(k[18], r1, r0, r3, 76, 26);
	keyiter(k[19], r2, r1, r4, 77, 27);
	keyiter(k[20], r3, r2, r0, 78, 28);
	keyiter(k[21], r4, r3, r1, 79, 29);
	keyiter(k[22], r0, r4, r2, 80, 30);
	keyiter(k[23], r1, r0, r3, 81, 31);

	k += 50;

	keyiter(k[-26], r2, r1, r4, 82, -18);
	keyiter(k[-25], r3, r2, r0, 83, -17);
	keyiter(k[-24], r4, r3, r1, 84, -16);
	keyiter(k[-23], r0, r4, r2, 85, -15);
	keyiter(k[-22], r1, r0, r3, 86, -14);
	keyiter(k[-21], r2, r1, r4, 87, -13);
	keyiter(k[-20], r3, r2, r0, 88, -12);
	keyiter(k[-19], r4, r3, r1, 89, -11);
	keyiter(k[-18], r0, r4, r2, 90, -10);
	keyiter(k[-17], r1, r0, r3, 91, -9);
	keyiter(k[-16], r2, r1, r4, 92, -8);
	keyiter(k[-15], r3, r2, r0, 93, -7);
	keyiter(k[-14], r4, r3, r1, 94, -6);
	keyiter(k[-13], r0, r4, r2, 95, -5);
	keyiter(k[-12], r1, r0, r3, 96, -4);
	keyiter(k[-11], r2, r1, r4, 97, -3);
	keyiter(k[-10], r3, r2, r0, 98, -2);
	keyiter(k[-9], r4, r3, r1, 99, -1);
	keyiter(k[-8], r0, r4, r2, 100, 0);
	keyiter(k[-7], r1, r0, r3, 101, 1);
	keyiter(k[-6], r2, r1, r4, 102, 2);
	keyiter(k[-5], r3, r2, r0, 103, 3);
	keyiter(k[-4], r4, r3, r1, 104, 4);
	keyiter(k[-3], r0, r4, r2, 105, 5);
	keyiter(k[-2], r1, r0, r3, 106, 6);
	keyiter(k[-1], r2, r1, r4, 107, 7);
	keyiter(k[0], r3, r2, r0, 108, 8);
	keyiter(k[1], r4, r3, r1, 109, 9);
	keyiter(k[2], r0, r4, r2, 110, 10);
	keyiter(k[3], r1, r0, r3, 111, 11);
	keyiter(k[4], r2, r1, r4, 112, 12);
	keyiter(k[5], r3, r2, r0, 113, 13);
	keyiter(k[6], r4, r3, r1, 114, 14);
	keyiter(k[7], r0, r4, r2, 115, 15);
	keyiter(k[8], r1, r0, r3, 116, 16);
	keyiter(k[9], r2, r1, r4, 117, 17);
	keyiter(k[10], r3, r2, r0, 118, 18);
	keyiter(k[11], r4, r3, r1, 119, 19);
	keyiter(k[12], r0, r4, r2, 120, 20);
	keyiter(k[13], r1, r0, r3, 121, 21);
	keyiter(k[14], r2, r1, r4, 122, 22);
	keyiter(k[15], r3, r2, r0, 123, 23);
	keyiter(k[16], r4, r3, r1, 124, 24);
	keyiter(k[17], r0, r4, r2, 125, 25);
	keyiter(k[18], r1, r0, r3, 126, 26);
	keyiter(k[19], r2, r1, r4, 127, 27);
	keyiter(k[20], r3, r2, r0, 128, 28);
	keyiter(k[21], r4, r3, r1, 129, 29);
	keyiter(k[22], r0, r4, r2, 130, 30);
	keyiter(k[23], r1, r0, r3, 131, 31);

	/* Apply S-boxes */
	__serpent_setkey_sbox(r0, r1, r2, r3, r4, ctx->expkey);

	return 0;
}