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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_tx_trig_level; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 

u_int16_t
ar9300_get_tx_trig_level(struct ath_hal *ah)
{
    return (AH9300(ah)->ah_tx_trig_level);
}