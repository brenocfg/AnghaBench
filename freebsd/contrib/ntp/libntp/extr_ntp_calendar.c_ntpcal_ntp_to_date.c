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
struct calendar {int dummy; } ;

/* Variables and functions */
 int ntpcal_ntp64_to_date (struct calendar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int
ntpcal_ntp_to_date(
	struct calendar *jd,
	uint32_t	 ntp,
	const time_t	*piv
	)
{
	vint64	ntp64;

	/*
	 * Unfold ntp time around current time into NTP domain. Split
	 * into days and seconds, shift days into CE domain and
	 * process the parts.
	 */
	ntp64 = ntpcal_ntp_to_ntp(ntp, piv);
	return ntpcal_ntp64_to_date(jd, &ntp64);
}