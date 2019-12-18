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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_SUBKEY_LR (int,int) ; 
 int rol32 (int,int) ; 

__attribute__((used)) static void camellia_setup_tail(u64 *subkey, u64 *subRL, int max)
{
	u64 kw4, tt;
	u32 dw, tl, tr;

	/* absorb kw2 to other subkeys */
	/* round 2 */
	subRL[3] ^= subRL[1];
	/* round 4 */
	subRL[5] ^= subRL[1];
	/* round 6 */
	subRL[7] ^= subRL[1];

	subRL[1] ^= (subRL[1] & ~subRL[9]) << 32;
	/* modified for FLinv(kl2) */
	dw = (subRL[1] & subRL[9]) >> 32;
	subRL[1] ^= rol32(dw, 1);

	/* round 8 */
	subRL[11] ^= subRL[1];
	/* round 10 */
	subRL[13] ^= subRL[1];
	/* round 12 */
	subRL[15] ^= subRL[1];

	subRL[1] ^= (subRL[1] & ~subRL[17]) << 32;
	/* modified for FLinv(kl4) */
	dw = (subRL[1] & subRL[17]) >> 32;
	subRL[1] ^= rol32(dw, 1);

	/* round 14 */
	subRL[19] ^= subRL[1];
	/* round 16 */
	subRL[21] ^= subRL[1];
	/* round 18 */
	subRL[23] ^= subRL[1];

	if (max == 24) {
		/* kw3 */
		subRL[24] ^= subRL[1];

		/* absorb kw4 to other subkeys */
		kw4 = subRL[25];
	} else {
		subRL[1] ^= (subRL[1] & ~subRL[25]) << 32;
		/* modified for FLinv(kl6) */
		dw = (subRL[1] & subRL[25]) >> 32;
		subRL[1] ^= rol32(dw, 1);

		/* round 20 */
		subRL[27] ^= subRL[1];
		/* round 22 */
		subRL[29] ^= subRL[1];
		/* round 24 */
		subRL[31] ^= subRL[1];
		/* kw3 */
		subRL[32] ^= subRL[1];

		/* absorb kw4 to other subkeys */
		kw4 = subRL[33];
		/* round 23 */
		subRL[30] ^= kw4;
		/* round 21 */
		subRL[28] ^= kw4;
		/* round 19 */
		subRL[26] ^= kw4;

		kw4 ^= (kw4 & ~subRL[24]) << 32;
		/* modified for FL(kl5) */
		dw = (kw4 & subRL[24]) >> 32;
		kw4 ^= rol32(dw, 1);
	}

	/* round 17 */
	subRL[22] ^= kw4;
	/* round 15 */
	subRL[20] ^= kw4;
	/* round 13 */
	subRL[18] ^= kw4;

	kw4 ^= (kw4 & ~subRL[16]) << 32;
	/* modified for FL(kl3) */
	dw = (kw4 & subRL[16]) >> 32;
	kw4 ^= rol32(dw, 1);

	/* round 11 */
	subRL[14] ^= kw4;
	/* round 9 */
	subRL[12] ^= kw4;
	/* round 7 */
	subRL[10] ^= kw4;

	kw4 ^= (kw4 & ~subRL[8]) << 32;
	/* modified for FL(kl1) */
	dw = (kw4 & subRL[8]) >> 32;
	kw4 ^= rol32(dw, 1);

	/* round 5 */
	subRL[6] ^= kw4;
	/* round 3 */
	subRL[4] ^= kw4;
	/* round 1 */
	subRL[2] ^= kw4;
	/* kw1 */
	subRL[0] ^= kw4;

	/* key XOR is end of F-function */
	SET_SUBKEY_LR(0, subRL[0] ^ subRL[2]);			/* kw1 */
	SET_SUBKEY_LR(2, subRL[3]);				/* round 1 */
	SET_SUBKEY_LR(3, subRL[2] ^ subRL[4]);			/* round 2 */
	SET_SUBKEY_LR(4, subRL[3] ^ subRL[5]);			/* round 3 */
	SET_SUBKEY_LR(5, subRL[4] ^ subRL[6]);			/* round 4 */
	SET_SUBKEY_LR(6, subRL[5] ^ subRL[7]);			/* round 5 */

	tl = (subRL[10] >> 32) ^ (subRL[10] & ~subRL[8]);
	dw = tl & (subRL[8] >> 32);				/* FL(kl1) */
	tr = subRL[10] ^ rol32(dw, 1);
	tt = (tr | ((u64)tl << 32));

	SET_SUBKEY_LR(7, subRL[6] ^ tt);			/* round 6 */
	SET_SUBKEY_LR(8, subRL[8]);				/* FL(kl1) */
	SET_SUBKEY_LR(9, subRL[9]);				/* FLinv(kl2) */

	tl = (subRL[7] >> 32) ^ (subRL[7] & ~subRL[9]);
	dw = tl & (subRL[9] >> 32);				/* FLinv(kl2) */
	tr = subRL[7] ^ rol32(dw, 1);
	tt = (tr | ((u64)tl << 32));

	SET_SUBKEY_LR(10, subRL[11] ^ tt);			/* round 7 */
	SET_SUBKEY_LR(11, subRL[10] ^ subRL[12]);		/* round 8 */
	SET_SUBKEY_LR(12, subRL[11] ^ subRL[13]);		/* round 9 */
	SET_SUBKEY_LR(13, subRL[12] ^ subRL[14]);		/* round 10 */
	SET_SUBKEY_LR(14, subRL[13] ^ subRL[15]);		/* round 11 */

	tl = (subRL[18] >> 32) ^ (subRL[18] & ~subRL[16]);
	dw = tl & (subRL[16] >> 32);				/* FL(kl3) */
	tr = subRL[18] ^ rol32(dw, 1);
	tt = (tr | ((u64)tl << 32));

	SET_SUBKEY_LR(15, subRL[14] ^ tt);			/* round 12 */
	SET_SUBKEY_LR(16, subRL[16]);				/* FL(kl3) */
	SET_SUBKEY_LR(17, subRL[17]);				/* FLinv(kl4) */

	tl = (subRL[15] >> 32) ^ (subRL[15] & ~subRL[17]);
	dw = tl & (subRL[17] >> 32);				/* FLinv(kl4) */
	tr = subRL[15] ^ rol32(dw, 1);
	tt = (tr | ((u64)tl << 32));

	SET_SUBKEY_LR(18, subRL[19] ^ tt);			/* round 13 */
	SET_SUBKEY_LR(19, subRL[18] ^ subRL[20]);		/* round 14 */
	SET_SUBKEY_LR(20, subRL[19] ^ subRL[21]);		/* round 15 */
	SET_SUBKEY_LR(21, subRL[20] ^ subRL[22]);		/* round 16 */
	SET_SUBKEY_LR(22, subRL[21] ^ subRL[23]);		/* round 17 */

	if (max == 24) {
		SET_SUBKEY_LR(23, subRL[22]);			/* round 18 */
		SET_SUBKEY_LR(24, subRL[24] ^ subRL[23]);	/* kw3 */
	} else {
		tl = (subRL[26] >> 32) ^ (subRL[26] & ~subRL[24]);
		dw = tl & (subRL[24] >> 32);			/* FL(kl5) */
		tr = subRL[26] ^ rol32(dw, 1);
		tt = (tr | ((u64)tl << 32));

		SET_SUBKEY_LR(23, subRL[22] ^ tt);		/* round 18 */
		SET_SUBKEY_LR(24, subRL[24]);			/* FL(kl5) */
		SET_SUBKEY_LR(25, subRL[25]);			/* FLinv(kl6) */

		tl = (subRL[23] >> 32) ^ (subRL[23] & ~subRL[25]);
		dw = tl & (subRL[25] >> 32);			/* FLinv(kl6) */
		tr = subRL[23] ^ rol32(dw, 1);
		tt = (tr | ((u64)tl << 32));

		SET_SUBKEY_LR(26, subRL[27] ^ tt);		/* round 19 */
		SET_SUBKEY_LR(27, subRL[26] ^ subRL[28]);	/* round 20 */
		SET_SUBKEY_LR(28, subRL[27] ^ subRL[29]);	/* round 21 */
		SET_SUBKEY_LR(29, subRL[28] ^ subRL[30]);	/* round 22 */
		SET_SUBKEY_LR(30, subRL[29] ^ subRL[31]);	/* round 23 */
		SET_SUBKEY_LR(31, subRL[30]);			/* round 24 */
		SET_SUBKEY_LR(32, subRL[32] ^ subRL[31]);	/* kw3 */
	}
}