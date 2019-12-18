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
struct ath_hal_9300 {int dummy; } ;

/* Variables and functions */

u_int8_t*
ar9300_eeprom_get_cust_data(struct ath_hal_9300 *ahp)
{
    return (u_int8_t *)ahp;
}