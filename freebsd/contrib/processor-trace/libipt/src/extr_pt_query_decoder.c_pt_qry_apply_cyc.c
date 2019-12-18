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
typedef  unsigned long long uint64_t ;
struct pt_time_cal {int dummy; } ;
struct pt_time {int dummy; } ;
struct pt_packet_cyc {int dummy; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pt_tcal_fcr (unsigned long long*,struct pt_time_cal*) ; 
 int pt_tcal_update_cyc (struct pt_time_cal*,struct pt_packet_cyc const*,struct pt_config const*) ; 
 int pt_time_update_cyc (struct pt_time*,struct pt_packet_cyc const*,struct pt_config const*,unsigned long long) ; 
 int pte_bad_config ; 
 int pte_no_time ; 

__attribute__((used)) static int pt_qry_apply_cyc(struct pt_time *time, struct pt_time_cal *tcal,
			    const struct pt_packet_cyc *packet,
			    const struct pt_config *config)
{
	uint64_t fcr;
	int errcode;

	/* We ignore configuration errors.  They will result in imprecise
	 * calibration which will result in imprecise cycle-accurate timing.
	 *
	 * We currently do not track them.
	 */
	errcode = pt_tcal_update_cyc(tcal, packet, config);
	if (errcode < 0 && (errcode != -pte_bad_config))
		return errcode;

	/* We need the FastCounter to Cycles ratio below.  Fall back to
	 * an invalid ratio of 0 if calibration has not kicked in, yet.
	 *
	 * This will be tracked as packet loss in struct pt_time.
	 */
	errcode = pt_tcal_fcr(&fcr, tcal);
	if (errcode < 0) {
		if (errcode == -pte_no_time)
			fcr = 0ull;
		else
			return errcode;
	}

	/* We ignore configuration errors.  They will result in imprecise
	 * timing and are tracked as packet losses in struct pt_time.
	 */
	errcode = pt_time_update_cyc(time, packet, config, fcr);
	if (errcode < 0 && (errcode != -pte_bad_config))
		return errcode;

	return 0;
}