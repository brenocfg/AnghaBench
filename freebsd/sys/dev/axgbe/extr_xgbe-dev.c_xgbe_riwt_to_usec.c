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
struct xgbe_prv_data {unsigned long sysclk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 

__attribute__((used)) static unsigned int xgbe_riwt_to_usec(struct xgbe_prv_data *pdata,
				      unsigned int riwt)
{
	unsigned long rate;
	unsigned int ret;

	DBGPR("-->xgbe_riwt_to_usec\n");

	rate = pdata->sysclk_rate;

	/*
	 * Convert the input watchdog timer value to the usec value. Each
	 * watchdog timer value is equivalent to 256 clock cycles.
	 * Calculate the required value as:
	 *   ( riwt * 256 ) / ( system_clock_mhz / 10^6 )
	 */
	ret = (riwt * 256) / (rate / 1000000);

	DBGPR("<--xgbe_riwt_to_usec\n");

	return ret;
}