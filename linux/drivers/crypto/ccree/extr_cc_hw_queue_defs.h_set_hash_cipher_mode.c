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
struct cc_hw_desc {int dummy; } ;
typedef  enum drv_hash_mode { ____Placeholder_drv_hash_mode } drv_hash_mode ;
typedef  enum drv_cipher_mode { ____Placeholder_drv_cipher_mode } drv_cipher_mode ;

/* Variables and functions */
 int DRV_HASH_SM3 ; 
 int /*<<< orphan*/  set_aes_xor_crypto_key (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int) ; 

__attribute__((used)) static inline void set_hash_cipher_mode(struct cc_hw_desc *pdesc,
					enum drv_cipher_mode cipher_mode,
					enum drv_hash_mode hash_mode)
{
	set_cipher_mode(pdesc, cipher_mode);
	if (hash_mode == DRV_HASH_SM3)
		set_aes_xor_crypto_key(pdesc);
}