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
typedef  enum drv_crypto_direction { ____Placeholder_drv_crypto_direction } drv_crypto_direction ;
typedef  enum cc_flow_mode { ____Placeholder_cc_flow_mode } cc_flow_mode ;

/* Variables and functions */
 int AES_and_HASH ; 
 int AES_to_HASH_and_DOUT ; 
 int DES_and_HASH ; 
 int DES_to_HASH_and_DOUT ; 
 int DIN_AES_DOUT ; 
 int DIN_DES_DOUT ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int S_DIN_to_AES ; 

__attribute__((used)) static enum cc_flow_mode cc_get_data_flow(enum drv_crypto_direction direct,
					  enum cc_flow_mode setup_flow_mode,
					  bool is_single_pass)
{
	enum cc_flow_mode data_flow_mode;

	if (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) {
		if (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = is_single_pass ?
				AES_to_HASH_and_DOUT : DIN_AES_DOUT;
		else
			data_flow_mode = is_single_pass ?
				DES_to_HASH_and_DOUT : DIN_DES_DOUT;
	} else { /* Decrypt */
		if (setup_flow_mode == S_DIN_to_AES)
			data_flow_mode = is_single_pass ?
				AES_and_HASH : DIN_AES_DOUT;
		else
			data_flow_mode = is_single_pass ?
				DES_and_HASH : DIN_DES_DOUT;
	}

	return data_flow_mode;
}