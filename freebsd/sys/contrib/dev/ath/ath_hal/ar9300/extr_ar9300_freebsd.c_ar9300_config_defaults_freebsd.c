#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ath_hal_enable_ani; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  int /*<<< orphan*/  HAL_OPS_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  OS_MEMCPY (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void
ar9300_config_defaults_freebsd(struct ath_hal *ah, HAL_OPS_CONFIG *ah_config)
{

	/* Until FreeBSD's HAL does this by default - just copy */
	OS_MEMCPY(&ah->ah_config, ah_config, sizeof(HAL_OPS_CONFIG));
	ah->ah_config.ath_hal_enable_ani = AH_TRUE;
}