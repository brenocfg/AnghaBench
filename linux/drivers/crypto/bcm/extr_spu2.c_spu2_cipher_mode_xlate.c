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
typedef  enum spu2_cipher_mode { ____Placeholder_spu2_cipher_mode } spu2_cipher_mode ;

/* Variables and functions */
#define  CIPHER_MODE_CBC 135 
#define  CIPHER_MODE_CCM 134 
#define  CIPHER_MODE_CFB 133 
#define  CIPHER_MODE_CTR 132 
#define  CIPHER_MODE_ECB 131 
#define  CIPHER_MODE_GCM 130 
#define  CIPHER_MODE_OFB 129 
#define  CIPHER_MODE_XTS 128 
 int EINVAL ; 
 int SPU2_CIPHER_MODE_CBC ; 
 int SPU2_CIPHER_MODE_CCM ; 
 int SPU2_CIPHER_MODE_CFB ; 
 int SPU2_CIPHER_MODE_CTR ; 
 int SPU2_CIPHER_MODE_ECB ; 
 int SPU2_CIPHER_MODE_GCM ; 
 int SPU2_CIPHER_MODE_OFB ; 
 int SPU2_CIPHER_MODE_XTS ; 

__attribute__((used)) static int spu2_cipher_mode_xlate(enum spu_cipher_mode cipher_mode,
				  enum spu2_cipher_mode *spu2_mode)
{
	switch (cipher_mode) {
	case CIPHER_MODE_ECB:
		*spu2_mode = SPU2_CIPHER_MODE_ECB;
		break;
	case CIPHER_MODE_CBC:
		*spu2_mode = SPU2_CIPHER_MODE_CBC;
		break;
	case CIPHER_MODE_OFB:
		*spu2_mode = SPU2_CIPHER_MODE_OFB;
		break;
	case CIPHER_MODE_CFB:
		*spu2_mode = SPU2_CIPHER_MODE_CFB;
		break;
	case CIPHER_MODE_CTR:
		*spu2_mode = SPU2_CIPHER_MODE_CTR;
		break;
	case CIPHER_MODE_CCM:
		*spu2_mode = SPU2_CIPHER_MODE_CCM;
		break;
	case CIPHER_MODE_GCM:
		*spu2_mode = SPU2_CIPHER_MODE_GCM;
		break;
	case CIPHER_MODE_XTS:
		*spu2_mode = SPU2_CIPHER_MODE_XTS;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}