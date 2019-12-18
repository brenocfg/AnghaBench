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

/* Variables and functions */
 void* linux_af_alg_skcipher (char*,int /*<<< orphan*/  const*,size_t) ; 

void * aes_decrypt_init(const u8 *key, size_t len)
{
	return linux_af_alg_skcipher("ecb(aes)", key, len);
}