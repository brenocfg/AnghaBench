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
typedef  unsigned int u32 ;
typedef  enum spu_cipher_mode { ____Placeholder_spu_cipher_mode } spu_cipher_mode ;

/* Variables and functions */
 int CIPHER_MODE_CCM ; 
 int CIPHER_MODE_GCM ; 
 unsigned int SPU_GCM_CCM_ALIGN ; 

u32 spum_gcm_ccm_pad_len(enum spu_cipher_mode cipher_mode,
			 unsigned int data_size)
{
	u32 pad_len = 0;
	u32 m1 = SPU_GCM_CCM_ALIGN - 1;

	if ((cipher_mode == CIPHER_MODE_GCM) ||
	    (cipher_mode == CIPHER_MODE_CCM))
		pad_len = ((data_size + m1) & ~m1) - data_size;

	return pad_len;
}