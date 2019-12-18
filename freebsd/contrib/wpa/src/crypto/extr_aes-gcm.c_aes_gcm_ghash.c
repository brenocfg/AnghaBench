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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  len_buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  WPA_PUT_BE64 (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ghash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghash_start (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void aes_gcm_ghash(const u8 *H, const u8 *aad, size_t aad_len,
			  const u8 *crypt, size_t crypt_len, u8 *S)
{
	u8 len_buf[16];

	/*
	 * u = 128 * ceil[len(C)/128] - len(C)
	 * v = 128 * ceil[len(A)/128] - len(A)
	 * S = GHASH_H(A || 0^v || C || 0^u || [len(A)]64 || [len(C)]64)
	 * (i.e., zero padded to block size A || C and lengths of each in bits)
	 */
	ghash_start(S);
	ghash(H, aad, aad_len, S);
	ghash(H, crypt, crypt_len, S);
	WPA_PUT_BE64(len_buf, aad_len * 8);
	WPA_PUT_BE64(len_buf + 8, crypt_len * 8);
	ghash(H, len_buf, sizeof(len_buf), S);

	wpa_hexdump_key(MSG_EXCESSIVE, "S = GHASH_H(...)", S, 16);
}