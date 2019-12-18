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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  aad_buf ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (size_t*,size_t) ; 
 int /*<<< orphan*/  aes_encrypt (void*,size_t*,size_t*) ; 
 int /*<<< orphan*/  os_memcpy (size_t*,size_t const*,size_t) ; 
 int /*<<< orphan*/  os_memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,size_t*,int) ; 
 int /*<<< orphan*/  xor_aes_block (size_t*,size_t*) ; 

__attribute__((used)) static void aes_ccm_auth_start(void *aes, size_t M, size_t L, const u8 *nonce,
			       const u8 *aad, size_t aad_len, size_t plain_len,
			       u8 *x)
{
	u8 aad_buf[2 * AES_BLOCK_SIZE];
	u8 b[AES_BLOCK_SIZE];

	/* Authentication */
	/* B_0: Flags | Nonce N | l(m) */
	b[0] = aad_len ? 0x40 : 0 /* Adata */;
	b[0] |= (((M - 2) / 2) /* M' */ << 3);
	b[0] |= (L - 1) /* L' */;
	os_memcpy(&b[1], nonce, 15 - L);
	WPA_PUT_BE16(&b[AES_BLOCK_SIZE - L], plain_len);

	wpa_hexdump_key(MSG_EXCESSIVE, "CCM B_0", b, AES_BLOCK_SIZE);
	aes_encrypt(aes, b, x); /* X_1 = E(K, B_0) */

	if (!aad_len)
		return;

	WPA_PUT_BE16(aad_buf, aad_len);
	os_memcpy(aad_buf + 2, aad, aad_len);
	os_memset(aad_buf + 2 + aad_len, 0, sizeof(aad_buf) - 2 - aad_len);

	xor_aes_block(aad_buf, x);
	aes_encrypt(aes, aad_buf, x); /* X_2 = E(K, X_1 XOR B_1) */

	if (aad_len > AES_BLOCK_SIZE - 2) {
		xor_aes_block(&aad_buf[AES_BLOCK_SIZE], x);
		/* X_3 = E(K, X_2 XOR B_2) */
		aes_encrypt(aes, &aad_buf[AES_BLOCK_SIZE], x);
	}
}