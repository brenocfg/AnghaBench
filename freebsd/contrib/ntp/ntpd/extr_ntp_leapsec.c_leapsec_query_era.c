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
typedef  int /*<<< orphan*/  leap_era_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  fetch_leap_era (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * leapsec_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int/*BOOL*/
leapsec_query_era(
	leap_era_t *   qr   ,
	uint32_t       ntpts,
	const time_t * pivot)
{
	const leap_table_t * pt;
	vint64               ts64;

	pt   = leapsec_get_table(FALSE);
	ts64 = ntpcal_ntp_to_ntp(ntpts, pivot);
	fetch_leap_era(qr, pt, &ts64);
	return TRUE;
}