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
 scalar_t__ aes_128_encrypt_block (int const*,int*,int*) ; 
 int aes_block_size ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 

int eap_psk_key_setup(const u8 *psk, u8 *ak, u8 *kdk)
{
	os_memset(ak, 0, aes_block_size);
	if (aes_128_encrypt_block(psk, ak, ak))
		return -1;
	os_memcpy(kdk, ak, aes_block_size);
	ak[aes_block_size - 1] ^= 0x01;
	kdk[aes_block_size - 1] ^= 0x02;
	if (aes_128_encrypt_block(psk, ak, ak) ||
	    aes_128_encrypt_block(psk, kdk, kdk))
		return -1;
	return 0;
}