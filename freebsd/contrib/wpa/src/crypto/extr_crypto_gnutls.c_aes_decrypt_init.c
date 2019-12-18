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
typedef  void* gcry_cipher_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRY_CIPHER_AES ; 
 int /*<<< orphan*/  GCRY_CIPHER_MODE_ECB ; 
 scalar_t__ GPG_ERR_NO_ERROR ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  gcry_cipher_close (void*) ; 
 scalar_t__ gcry_cipher_open (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_cipher_setkey (void*,int /*<<< orphan*/  const*,size_t) ; 

void * aes_decrypt_init(const u8 *key, size_t len)
{
	gcry_cipher_hd_t hd;

	if (TEST_FAIL())
		return NULL;

	if (gcry_cipher_open(&hd, GCRY_CIPHER_AES, GCRY_CIPHER_MODE_ECB, 0) !=
	    GPG_ERR_NO_ERROR)
		return NULL;
	if (gcry_cipher_setkey(hd, key, len) != GPG_ERR_NO_ERROR) {
		gcry_cipher_close(hd);
		return NULL;
	}

	return hd;
}