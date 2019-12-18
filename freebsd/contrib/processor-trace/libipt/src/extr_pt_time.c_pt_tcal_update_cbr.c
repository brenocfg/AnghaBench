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
struct pt_time_cal {int dummy; } ;
struct pt_packet_cbr {int dummy; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pt_tcal_header_cbr (struct pt_time_cal*,struct pt_packet_cbr const*,struct pt_config const*) ; 
 int /*<<< orphan*/  pt_tcal_init (struct pt_time_cal*) ; 

int pt_tcal_update_cbr(struct pt_time_cal *tcal,
		      const struct pt_packet_cbr *packet,
		      const struct pt_config *config)
{
	/* A CBR outside of PSB+ indicates a frequency change.  Reset our
	 * calibration state.
	 */
	pt_tcal_init(tcal);

	return pt_tcal_header_cbr(tcal, packet, config);
}