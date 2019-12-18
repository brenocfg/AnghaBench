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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_MFP_QOSDATA ; 

__attribute__((used)) static inline u_int32_t
ath_hal_get_mfp_qos(struct ath_hal *ah)
{
	//return AH_PRIVATE(ah)->ah_mfp_qos;
	return HAL_MFP_QOSDATA;
}