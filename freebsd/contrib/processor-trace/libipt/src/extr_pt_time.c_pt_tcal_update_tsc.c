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
struct pt_time_cal {unsigned long long cyc_tsc; int /*<<< orphan*/  tsc; } ;
struct pt_packet_tsc {int /*<<< orphan*/  tsc; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_tcal_update_tsc(struct pt_time_cal *tcal,
		      const struct pt_packet_tsc *packet,
		      const struct pt_config *config)
{
	(void) config;

	if (!tcal || !packet)
		return -pte_internal;

	/* A TSC outside of PSB+ may indicate loss of time.  We do not use it
	 * for calibration.  We store the TSC value for calibration at the next
	 * TSC in PSB+, though.
	 */
	tcal->tsc = packet->tsc;
	tcal->cyc_tsc = 0ull;

	return 0;
}