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
struct al_eth_kr_status_report_data {scalar_t__ c_zero; scalar_t__ c_minus; scalar_t__ c_plus; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ C72_CSTATE_NOT_UPDATED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
al_eth_kr_lt_all_not_updated(struct al_eth_kr_status_report_data *report)
{

	if ((report->c_zero == C72_CSTATE_NOT_UPDATED) &&
	    (report->c_minus == C72_CSTATE_NOT_UPDATED) &&
	    (report->c_plus == C72_CSTATE_NOT_UPDATED)) {
		return (TRUE);
	}

	return (FALSE);
}