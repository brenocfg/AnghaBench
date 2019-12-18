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
typedef  enum spu_cipher_mode { ____Placeholder_spu_cipher_mode } spu_cipher_mode ;
typedef  enum spu_cipher_alg { ____Placeholder_spu_cipher_alg } spu_cipher_alg ;

/* Variables and functions */
#define  CIPHER_ALG_3DES 138 
#define  CIPHER_ALG_AES 137 
#define  CIPHER_ALG_DES 136 
#define  CIPHER_ALG_RC4 135 
#define  CIPHER_MODE_CBC 134 
#define  CIPHER_MODE_CFB 133 
#define  CIPHER_MODE_CTR 132 
#define  CIPHER_MODE_ECB 131 
#define  CIPHER_MODE_GCM 130 
#define  CIPHER_MODE_OFB 129 
#define  CIPHER_MODE_XTS 128 

char *spu_alg_name(enum spu_cipher_alg alg, enum spu_cipher_mode mode)
{
	switch (alg) {
	case CIPHER_ALG_RC4:
		return "rc4";
	case CIPHER_ALG_AES:
		switch (mode) {
		case CIPHER_MODE_CBC:
			return "cbc(aes)";
		case CIPHER_MODE_ECB:
			return "ecb(aes)";
		case CIPHER_MODE_OFB:
			return "ofb(aes)";
		case CIPHER_MODE_CFB:
			return "cfb(aes)";
		case CIPHER_MODE_CTR:
			return "ctr(aes)";
		case CIPHER_MODE_XTS:
			return "xts(aes)";
		case CIPHER_MODE_GCM:
			return "gcm(aes)";
		default:
			return "aes";
		}
		break;
	case CIPHER_ALG_DES:
		switch (mode) {
		case CIPHER_MODE_CBC:
			return "cbc(des)";
		case CIPHER_MODE_ECB:
			return "ecb(des)";
		case CIPHER_MODE_CTR:
			return "ctr(des)";
		default:
			return "des";
		}
		break;
	case CIPHER_ALG_3DES:
		switch (mode) {
		case CIPHER_MODE_CBC:
			return "cbc(des3_ede)";
		case CIPHER_MODE_ECB:
			return "ecb(des3_ede)";
		case CIPHER_MODE_CTR:
			return "ctr(des3_ede)";
		default:
			return "3des";
		}
		break;
	default:
		return "other";
	}
}