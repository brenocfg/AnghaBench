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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 scalar_t__ ENCR_ALG_AES ; 
 scalar_t__ ENCR_ALG_DES ; 
 scalar_t__ ENCR_ALG_SHIFT ; 
 scalar_t__ ENCR_KEY_SZ_3DES ; 
 scalar_t__ ENCR_KEY_SZ_AES128 ; 
 scalar_t__ ENCR_KEY_SZ_AES256 ; 
 scalar_t__ ENCR_KEY_SZ_DES ; 
 scalar_t__ ENCR_KEY_SZ_SHIFT ; 
 scalar_t__ ENCR_MODE_CBC ; 
 scalar_t__ ENCR_MODE_CCM ; 
 scalar_t__ ENCR_MODE_CTR ; 
 scalar_t__ ENCR_MODE_ECB ; 
 scalar_t__ ENCR_MODE_SHIFT ; 
 scalar_t__ ENCR_MODE_XTS ; 
 scalar_t__ IS_3DES (unsigned long) ; 
 scalar_t__ IS_AES (unsigned long) ; 
 scalar_t__ IS_DES (unsigned long) ; 
 scalar_t__ LAST_CCM_SHIFT ; 
 scalar_t__ LAST_CCM_XFR ; 
#define  QCE_MODE_CBC 132 
#define  QCE_MODE_CCM 131 
#define  QCE_MODE_CTR 130 
#define  QCE_MODE_ECB 129 
 unsigned long QCE_MODE_MASK ; 
#define  QCE_MODE_XTS 128 

__attribute__((used)) static u32 qce_encr_cfg(unsigned long flags, u32 aes_key_size)
{
	u32 cfg = 0;

	if (IS_AES(flags)) {
		if (aes_key_size == AES_KEYSIZE_128)
			cfg |= ENCR_KEY_SZ_AES128 << ENCR_KEY_SZ_SHIFT;
		else if (aes_key_size == AES_KEYSIZE_256)
			cfg |= ENCR_KEY_SZ_AES256 << ENCR_KEY_SZ_SHIFT;
	}

	if (IS_AES(flags))
		cfg |= ENCR_ALG_AES << ENCR_ALG_SHIFT;
	else if (IS_DES(flags) || IS_3DES(flags))
		cfg |= ENCR_ALG_DES << ENCR_ALG_SHIFT;

	if (IS_DES(flags))
		cfg |= ENCR_KEY_SZ_DES << ENCR_KEY_SZ_SHIFT;

	if (IS_3DES(flags))
		cfg |= ENCR_KEY_SZ_3DES << ENCR_KEY_SZ_SHIFT;

	switch (flags & QCE_MODE_MASK) {
	case QCE_MODE_ECB:
		cfg |= ENCR_MODE_ECB << ENCR_MODE_SHIFT;
		break;
	case QCE_MODE_CBC:
		cfg |= ENCR_MODE_CBC << ENCR_MODE_SHIFT;
		break;
	case QCE_MODE_CTR:
		cfg |= ENCR_MODE_CTR << ENCR_MODE_SHIFT;
		break;
	case QCE_MODE_XTS:
		cfg |= ENCR_MODE_XTS << ENCR_MODE_SHIFT;
		break;
	case QCE_MODE_CCM:
		cfg |= ENCR_MODE_CCM << ENCR_MODE_SHIFT;
		cfg |= LAST_CCM_XFR << LAST_CCM_SHIFT;
		break;
	default:
		return ~0;
	}

	return cfg;
}