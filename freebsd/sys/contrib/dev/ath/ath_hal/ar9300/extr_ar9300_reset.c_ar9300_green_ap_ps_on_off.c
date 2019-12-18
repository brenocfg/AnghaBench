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
struct TYPE_2__ {int green_ap_ps_on; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 

void
ar9300_green_ap_ps_on_off( struct ath_hal *ah, u_int16_t on_off)
{
    /* Set/reset the ps flag */
    AH9300(ah)->green_ap_ps_on = !!on_off;
}