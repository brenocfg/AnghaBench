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
struct freq_survey {int filled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int SURVEY_HAS_CHAN_TIME ; 
 int SURVEY_HAS_CHAN_TIME_BUSY ; 
 int SURVEY_HAS_CHAN_TIME_RX ; 
 int SURVEY_HAS_NF ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int acs_survey_is_sufficient(struct freq_survey *survey)
{
	if (!(survey->filled & SURVEY_HAS_NF)) {
		wpa_printf(MSG_INFO, "ACS: Survey is missing noise floor");
		return 0;
	}

	if (!(survey->filled & SURVEY_HAS_CHAN_TIME)) {
		wpa_printf(MSG_INFO, "ACS: Survey is missing channel time");
		return 0;
	}

	if (!(survey->filled & SURVEY_HAS_CHAN_TIME_BUSY) &&
	    !(survey->filled & SURVEY_HAS_CHAN_TIME_RX)) {
		wpa_printf(MSG_INFO,
			   "ACS: Survey is missing RX and busy time (at least one is required)");
		return 0;
	}

	return 1;
}