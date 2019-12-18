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
typedef  int /*<<< orphan*/  gcry_cipher_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRY_CIPHER_DES ; 
 int /*<<< orphan*/  GCRY_CIPHER_MODE_ECB ; 
 int /*<<< orphan*/  gcry_cipher_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_cipher_encrypt (int /*<<< orphan*/ ,int*,int,int const*,int) ; 
 int /*<<< orphan*/  gcry_cipher_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_cipher_setkey (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  gcry_err_code (int /*<<< orphan*/ ) ; 

int des_encrypt(const u8 *clear, const u8 *key, u8 *cypher)
{
	gcry_cipher_hd_t hd;
	u8 pkey[8], next, tmp;
	int i;

	/* Add parity bits to the key */
	next = 0;
	for (i = 0; i < 7; i++) {
		tmp = key[i];
		pkey[i] = (tmp >> i) | next | 1;
		next = tmp << (7 - i);
	}
	pkey[i] = next | 1;

	gcry_cipher_open(&hd, GCRY_CIPHER_DES, GCRY_CIPHER_MODE_ECB, 0);
	gcry_err_code(gcry_cipher_setkey(hd, pkey, 8));
	gcry_cipher_encrypt(hd, cypher, 8, clear, 8);
	gcry_cipher_close(hd);
	return 0;
}