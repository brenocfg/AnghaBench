#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint16_t ;
struct ath_hal_5416 {int /*<<< orphan*/ * ah_keytype; } ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {size_t kv_type; } ;
typedef  TYPE_1__ HAL_KEYVAL ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ ar5212SetKeyCacheEntry (struct ath_hal*,size_t,TYPE_1__ const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * keyType ; 

HAL_BOOL
ar5416SetKeyCacheEntry(struct ath_hal *ah, uint16_t entry,
                       const HAL_KEYVAL *k, const uint8_t *mac,
                       int xorKey)
{
	struct ath_hal_5416 *ahp = AH5416(ah);

	if (ar5212SetKeyCacheEntry(ah, entry, k, mac, xorKey)) {
		ahp->ah_keytype[entry] = keyType[k->kv_type];
		return AH_TRUE;
	} else
		return AH_FALSE;
}