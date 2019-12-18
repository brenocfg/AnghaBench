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
typedef  unsigned int u8 ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_decrypt (void*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  aes_decrypt_deinit (void*) ; 
 void* aes_decrypt_init (unsigned int const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (unsigned int*,unsigned int const*,int) ; 

int aes_unwrap(const u8 *kek, size_t kek_len, int n, const u8 *cipher,
	       u8 *plain)
{
	u8 a[8], *r, b[AES_BLOCK_SIZE];
	int i, j;
	void *ctx;
	unsigned int t;

	/* 1) Initialize variables. */
	os_memcpy(a, cipher, 8);
	r = plain;
	os_memcpy(r, cipher + 8, 8 * n);

	ctx = aes_decrypt_init(kek, kek_len);
	if (ctx == NULL)
		return -1;

	/* 2) Compute intermediate values.
	 * For j = 5 to 0
	 *     For i = n to 1
	 *         B = AES-1(K, (A ^ t) | R[i]) where t = n*j+i
	 *         A = MSB(64, B)
	 *         R[i] = LSB(64, B)
	 */
	for (j = 5; j >= 0; j--) {
		r = plain + (n - 1) * 8;
		for (i = n; i >= 1; i--) {
			os_memcpy(b, a, 8);
			t = n * j + i;
			b[7] ^= t;
			b[6] ^= t >> 8;
			b[5] ^= t >> 16;
			b[4] ^= t >> 24;

			os_memcpy(b + 8, r, 8);
			aes_decrypt(ctx, b, b);
			os_memcpy(a, b, 8);
			os_memcpy(r, b + 8, 8);
			r -= 8;
		}
	}
	aes_decrypt_deinit(ctx);

	/* 3) Output results.
	 *
	 * These are already in @plain due to the location of temporary
	 * variables. Just verify that the IV matches with the expected value.
	 */
	for (i = 0; i < 8; i++) {
		if (a[i] != 0xa6)
			return -1;
	}

	return 0;
}