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
struct cc_cipher_ctx {int flow_mode; int /*<<< orphan*/  cipher_mode; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int DES_BLOCK_SIZE ; 
#define  DRV_CIPHER_BITLOCKER 138 
#define  DRV_CIPHER_CBC 137 
#define  DRV_CIPHER_CBC_CTS 136 
#define  DRV_CIPHER_CTR 135 
#define  DRV_CIPHER_ECB 134 
#define  DRV_CIPHER_ESSIV 133 
#define  DRV_CIPHER_OFB 132 
#define  DRV_CIPHER_XTS 131 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,unsigned int) ; 
 unsigned int SM4_BLOCK_SIZE ; 
#define  S_DIN_to_AES 130 
#define  S_DIN_to_DES 129 
#define  S_DIN_to_SM4 128 

__attribute__((used)) static int validate_data_size(struct cc_cipher_ctx *ctx_p,
			      unsigned int size)
{
	switch (ctx_p->flow_mode) {
	case S_DIN_to_AES:
		switch (ctx_p->cipher_mode) {
		case DRV_CIPHER_XTS:
		case DRV_CIPHER_CBC_CTS:
			if (size >= AES_BLOCK_SIZE)
				return 0;
			break;
		case DRV_CIPHER_OFB:
		case DRV_CIPHER_CTR:
				return 0;
		case DRV_CIPHER_ECB:
		case DRV_CIPHER_CBC:
		case DRV_CIPHER_ESSIV:
		case DRV_CIPHER_BITLOCKER:
			if (IS_ALIGNED(size, AES_BLOCK_SIZE))
				return 0;
			break;
		default:
			break;
		}
		break;
	case S_DIN_to_DES:
		if (IS_ALIGNED(size, DES_BLOCK_SIZE))
			return 0;
		break;
	case S_DIN_to_SM4:
		switch (ctx_p->cipher_mode) {
		case DRV_CIPHER_CTR:
			return 0;
		case DRV_CIPHER_ECB:
		case DRV_CIPHER_CBC:
			if (IS_ALIGNED(size, SM4_BLOCK_SIZE))
				return 0;
		default:
			break;
		}
	default:
		break;
	}
	return -EINVAL;
}