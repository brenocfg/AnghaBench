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

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int CHCR_KEYCTX_CIPHER_KEY_SIZE_128 ; 
 int CHCR_KEYCTX_CIPHER_KEY_SIZE_192 ; 
 int CHCR_KEYCTX_CIPHER_KEY_SIZE_256 ; 

__attribute__((used)) static inline int chcr_keyctx_ck_size(unsigned int keylen)
{
	int ck_size = 0;

	if (keylen == AES_KEYSIZE_128)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	else if (keylen == AES_KEYSIZE_192)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	else if (keylen == AES_KEYSIZE_256)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	else
		ck_size = 0;

	return ck_size;
}