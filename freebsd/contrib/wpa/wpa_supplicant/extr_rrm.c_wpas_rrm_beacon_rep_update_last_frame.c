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
typedef  int u8 ;
struct rrm_measurement_report_element {int len; scalar_t__ eid; scalar_t__ type; scalar_t__ variable; } ;
struct rrm_measurement_beacon_report {int* variable; } ;

/* Variables and functions */
 int BEACON_REPORT_LAST_INDICATION_SUBELEM_LEN ; 
 scalar_t__ MEASURE_TYPE_BEACON ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WLAN_BEACON_REPORT_SUBELEM_LAST_INDICATION ; 
 scalar_t__ WLAN_EID_MEASURE_REPORT ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpas_rrm_beacon_rep_update_last_frame(u8 *pos, size_t len)
{
	struct rrm_measurement_report_element *msr_rep;
	u8 *end = pos + len;
	u8 *msr_rep_end;
	struct rrm_measurement_beacon_report *rep = NULL;
	u8 *subelem;

	/* Find the last beacon report element */
	while (end - pos >= (int) sizeof(*msr_rep)) {
		msr_rep = (struct rrm_measurement_report_element *) pos;
		msr_rep_end = pos + msr_rep->len + 2;

		if (msr_rep->eid != WLAN_EID_MEASURE_REPORT ||
		    msr_rep_end > end) {
			/* Should not happen. This indicates a bug. */
			wpa_printf(MSG_ERROR,
				   "RRM: non-measurement report element in measurement report frame");
			return -1;
		}

		if (msr_rep->type == MEASURE_TYPE_BEACON)
			rep = (struct rrm_measurement_beacon_report *)
				msr_rep->variable;

		pos += pos[1] + 2;
	}

	if (!rep)
		return 0;

	subelem = rep->variable;
	while (subelem + 2 < msr_rep_end &&
	       subelem[0] != WLAN_BEACON_REPORT_SUBELEM_LAST_INDICATION)
		subelem += 2 + subelem[1];

	if (subelem + 2 < msr_rep_end &&
	    subelem[0] == WLAN_BEACON_REPORT_SUBELEM_LAST_INDICATION &&
	    subelem[1] == 1 &&
	    subelem + BEACON_REPORT_LAST_INDICATION_SUBELEM_LEN <= end)
		subelem[2] = 1;

	return 0;
}