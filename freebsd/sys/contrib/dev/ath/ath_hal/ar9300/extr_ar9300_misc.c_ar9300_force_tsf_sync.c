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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_M_STA ; 
 int /*<<< orphan*/  ar9300_set_operating_mode (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_write_associd (struct ath_hal*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
ar9300_force_tsf_sync(struct ath_hal *ah, const u_int8_t *bssid,
    u_int16_t assoc_id)
{
    ar9300_set_operating_mode(ah, HAL_M_STA);
    ar9300_write_associd(ah, bssid, assoc_id);
}