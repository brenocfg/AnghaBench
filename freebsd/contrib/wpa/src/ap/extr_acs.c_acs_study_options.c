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
struct hostapd_iface {int dummy; } ;

/* Variables and functions */
 scalar_t__ acs_study_survey_based (struct hostapd_iface*) ; 

__attribute__((used)) static int acs_study_options(struct hostapd_iface *iface)
{
	if (acs_study_survey_based(iface) == 0)
		return 0;

	/* TODO: If no surveys are available/sufficient this is a good
	 * place to fallback to BSS-based ACS */

	return -1;
}