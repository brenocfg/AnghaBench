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
typedef  size_t u32 ;
struct crypto_aes_ctx {int /*<<< orphan*/  key_enc; } ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ce_aes_ccm_auth_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_simd_usable () ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int min (size_t,size_t) ; 
 int /*<<< orphan*/  num_rounds (struct crypto_aes_ctx*) ; 

__attribute__((used)) static void ccm_update_mac(struct crypto_aes_ctx *key, u8 mac[], u8 const in[],
			   u32 abytes, u32 *macp)
{
	if (crypto_simd_usable()) {
		kernel_neon_begin();
		ce_aes_ccm_auth_data(mac, in, abytes, macp, key->key_enc,
				     num_rounds(key));
		kernel_neon_end();
	} else {
		if (*macp > 0 && *macp < AES_BLOCK_SIZE) {
			int added = min(abytes, AES_BLOCK_SIZE - *macp);

			crypto_xor(&mac[*macp], in, added);

			*macp += added;
			in += added;
			abytes -= added;
		}

		while (abytes >= AES_BLOCK_SIZE) {
			aes_encrypt(key, mac, mac);
			crypto_xor(mac, in, AES_BLOCK_SIZE);

			in += AES_BLOCK_SIZE;
			abytes -= AES_BLOCK_SIZE;
		}

		if (abytes > 0) {
			aes_encrypt(key, mac, mac);
			crypto_xor(mac, in, abytes);
			*macp = abytes;
		}
	}
}