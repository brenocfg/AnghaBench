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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;

/* Variables and functions */
#define  HAL_CAP_CIPHER 131 
#define  HAL_CIPHER_AES_OCB 130 
#define  HAL_CIPHER_CLR 129 
#define  HAL_CIPHER_WEP 128 
 int /*<<< orphan*/  HAL_ENOTSUPP ; 
 int /*<<< orphan*/  HAL_OK ; 
 int /*<<< orphan*/  ath_hal_getcapability (struct ath_hal*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HAL_STATUS
ar5211GetCapability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
	uint32_t capability, uint32_t *result)
{

	switch (type) {
	case HAL_CAP_CIPHER:		/* cipher handled in hardware */
		switch (capability) {
		case HAL_CIPHER_AES_OCB:
		case HAL_CIPHER_WEP:
		case HAL_CIPHER_CLR:
			return HAL_OK;
		default:
			return HAL_ENOTSUPP;
		}
	default:
		return ath_hal_getcapability(ah, type, capability, result);
	}
}