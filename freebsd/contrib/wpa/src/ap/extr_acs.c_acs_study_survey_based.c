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
struct hostapd_iface {int /*<<< orphan*/  chans_surveyed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  acs_survey_all_chans_intereference_factor (struct hostapd_iface*) ; 
 int /*<<< orphan*/  acs_surveys_are_sufficient (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int acs_study_survey_based(struct hostapd_iface *iface)
{
	wpa_printf(MSG_DEBUG, "ACS: Trying survey-based ACS");

	if (!iface->chans_surveyed) {
		wpa_printf(MSG_ERROR, "ACS: Unable to collect survey data");
		return -1;
	}

	if (!acs_surveys_are_sufficient(iface)) {
		wpa_printf(MSG_ERROR, "ACS: Surveys have insufficient data");
		return -1;
	}

	acs_survey_all_chans_intereference_factor(iface);
	return 0;
}