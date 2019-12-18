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
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  leap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ leapsec_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * leapsec_get_table (int /*<<< orphan*/ ) ; 
 scalar_t__ leapsec_set_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int/*BOOL*/
leapsec_add_dyn(
	int            insert,
	uint32_t       ntpnow,
	const time_t * pivot )
{
	leap_table_t * pt;
	vint64         now64;

	pt = leapsec_get_table(TRUE);
	now64 = ntpcal_ntp_to_ntp(ntpnow, pivot);
	return (   leapsec_add(pt, &now64, (insert != 0))
		&& leapsec_set_table(pt));
}