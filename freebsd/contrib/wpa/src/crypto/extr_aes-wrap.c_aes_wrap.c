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
 int /*<<< orphan*/  aes_encrypt (void*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  aes_encrypt_deinit (void*) ; 
 void* aes_encrypt_init (unsigned int const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (unsigned int*,unsigned int const*,int) ; 
 int /*<<< orphan*/  os_memset (unsigned int*,int,int) ; 

int aes_wrap(const u8 *kek, size_t kek_len, int n, const u8 *plain, u8 *cipher)
{
	u8 *a, *r, b[AES_BLOCK_SIZE];
	int i, j;
	void *ctx;
	unsigned int t;

	a = cipher;
	r = cipher + 8;

	/* 1) Initialize variables. */
	os_memset(a, 0xa6, 8);
	os_memcpy(r, plain, 8 * n);

	ctx = aes_encrypt_init(kek, kek_len);
	if (ctx == NULL)
		return -1;

	/* 2) Calculate intermediate values.
	 * For j = 0 to 5
	 *     For i=1 to n
	 *         B = AES(K, A | R[i])
	 *         A = MSB(64, B) ^ t where t = (n*j)+i
	 *         R[i] = LSB(64, B)
	 */
	for (j = 0; j <= 5; j++) {
		r = cipher + 8;
		for (i = 1; i <= n; i++) {
			os_memcpy(b, a, 8);
			os_memcpy(b + 8, r, 8);
			aes_encrypt(ctx, b, b);
			os_memcpy(a, b, 8);
			t = n * j + i;
			a[7] ^= t;
			a[6] ^= t >> 8;
			a[5] ^= t >> 16;
			a[4] ^= t >> 24;
			os_memcpy(r, b + 8, 8);
			r += 8;
		}
	}
	aes_encrypt_deinit(ctx);

	/* 3) Output the results.
	 *
	 * These are already in @cipher due to the location of temporary
	 * variables.
	 */

	return 0;
}