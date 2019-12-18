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
typedef  int HAL_BOOL ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO2 ; 

__attribute__((used)) static HAL_BOOL
ath_is_alt_ant_ratio_better(int alt_ratio, int maxdelta, int mindelta,
    int main_rssi_avg, int alt_rssi_avg, int pkt_count)
{
	return (((alt_ratio >= ATH_ANT_DIV_COMB_ALT_ANT_RATIO2) &&
		(alt_rssi_avg > main_rssi_avg + maxdelta)) ||
		(alt_rssi_avg > main_rssi_avg + mindelta)) && (pkt_count > 50);
}