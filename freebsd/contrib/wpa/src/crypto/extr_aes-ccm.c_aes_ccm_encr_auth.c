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

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_encrypt (void*,int*,int*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int*,size_t) ; 

__attribute__((used)) static void aes_ccm_encr_auth(void *aes, size_t M, u8 *x, u8 *a, u8 *auth)
{
	size_t i;
	u8 tmp[AES_BLOCK_SIZE];

	wpa_hexdump_key(MSG_EXCESSIVE, "CCM T", x, M);
	/* U = T XOR S_0; S_0 = E(K, A_0) */
	WPA_PUT_BE16(&a[AES_BLOCK_SIZE - 2], 0);
	aes_encrypt(aes, a, tmp);
	for (i = 0; i < M; i++)
		auth[i] = x[i] ^ tmp[i];
	wpa_hexdump_key(MSG_EXCESSIVE, "CCM U", auth, M);
}