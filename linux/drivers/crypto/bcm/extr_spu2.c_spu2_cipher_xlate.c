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
typedef  enum spu_cipher_type { ____Placeholder_spu_cipher_type } spu_cipher_type ;
typedef  enum spu_cipher_mode { ____Placeholder_spu_cipher_mode } spu_cipher_mode ;
typedef  enum spu_cipher_alg { ____Placeholder_spu_cipher_alg } spu_cipher_alg ;
typedef  enum spu2_cipher_type { ____Placeholder_spu2_cipher_type } spu2_cipher_type ;
typedef  enum spu2_cipher_mode { ____Placeholder_spu2_cipher_mode } spu2_cipher_mode ;

/* Variables and functions */
#define  CIPHER_ALG_3DES 136 
#define  CIPHER_ALG_AES 135 
#define  CIPHER_ALG_DES 134 
#define  CIPHER_ALG_LAST 133 
#define  CIPHER_ALG_NONE 132 
#define  CIPHER_ALG_RC4 131 
#define  CIPHER_TYPE_AES128 130 
#define  CIPHER_TYPE_AES192 129 
#define  CIPHER_TYPE_AES256 128 
 int EINVAL ; 
 int SPU2_CIPHER_TYPE_3DES ; 
 int SPU2_CIPHER_TYPE_AES128 ; 
 int SPU2_CIPHER_TYPE_AES192 ; 
 int SPU2_CIPHER_TYPE_AES256 ; 
 int SPU2_CIPHER_TYPE_DES ; 
 int SPU2_CIPHER_TYPE_NONE ; 
 int /*<<< orphan*/  flow_log (char*,int,...) ; 
 int spu2_cipher_mode_xlate (int,int*) ; 

__attribute__((used)) static int spu2_cipher_xlate(enum spu_cipher_alg cipher_alg,
			     enum spu_cipher_mode cipher_mode,
			     enum spu_cipher_type cipher_type,
			     enum spu2_cipher_type *spu2_type,
			     enum spu2_cipher_mode *spu2_mode)
{
	int err;

	err = spu2_cipher_mode_xlate(cipher_mode, spu2_mode);
	if (err) {
		flow_log("Invalid cipher mode %d\n", cipher_mode);
		return err;
	}

	switch (cipher_alg) {
	case CIPHER_ALG_NONE:
		*spu2_type = SPU2_CIPHER_TYPE_NONE;
		break;
	case CIPHER_ALG_RC4:
		/* SPU2 does not support RC4 */
		err = -EINVAL;
		*spu2_type = SPU2_CIPHER_TYPE_NONE;
		break;
	case CIPHER_ALG_DES:
		*spu2_type = SPU2_CIPHER_TYPE_DES;
		break;
	case CIPHER_ALG_3DES:
		*spu2_type = SPU2_CIPHER_TYPE_3DES;
		break;
	case CIPHER_ALG_AES:
		switch (cipher_type) {
		case CIPHER_TYPE_AES128:
			*spu2_type = SPU2_CIPHER_TYPE_AES128;
			break;
		case CIPHER_TYPE_AES192:
			*spu2_type = SPU2_CIPHER_TYPE_AES192;
			break;
		case CIPHER_TYPE_AES256:
			*spu2_type = SPU2_CIPHER_TYPE_AES256;
			break;
		default:
			err = -EINVAL;
		}
		break;
	case CIPHER_ALG_LAST:
	default:
		err = -EINVAL;
		break;
	}

	if (err)
		flow_log("Invalid cipher alg %d or type %d\n",
			 cipher_alg, cipher_type);
	return err;
}