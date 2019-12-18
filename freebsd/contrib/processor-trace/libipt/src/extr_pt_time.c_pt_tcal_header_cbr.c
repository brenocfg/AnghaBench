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
typedef  int uint64_t ;
struct pt_time_cal {int dummy; } ;
struct pt_packet_cbr {int ratio; } ;
struct pt_config {int nom_freq; } ;

/* Variables and functions */
 int pt_tcal_fcr_shr ; 
 int pt_tcal_set_fcr (struct pt_time_cal*,int) ; 
 int pte_bad_packet ; 
 int pte_internal ; 

int pt_tcal_header_cbr(struct pt_time_cal *tcal,
		      const struct pt_packet_cbr *packet,
		      const struct pt_config *config)
{
	uint64_t cbr, p1, fcr;

	if (!tcal || !packet || !config)
		return -pte_internal;

	p1 = config->nom_freq;
	if (!p1)
		return 0;

	/* If we know the nominal frequency, we can use it for calibration. */
	cbr = packet->ratio;
	if (!cbr)
		return -pte_bad_packet;

	fcr = (p1 << pt_tcal_fcr_shr) / cbr;

	return pt_tcal_set_fcr(tcal, fcr);
}