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
struct timespec {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ acpi_battery_get_info_expire () ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  smbat ; 
 int /*<<< orphan*/  timespecisset (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static int
acpi_smbat_info_expired(struct timespec *lastupdated)
{
	struct timespec	curtime;

	ACPI_SERIAL_ASSERT(smbat);

	if (lastupdated == NULL)
		return (TRUE);
	if (!timespecisset(lastupdated))
		return (TRUE);

	getnanotime(&curtime);
	timespecsub(&curtime, lastupdated, &curtime);
	return (curtime.tv_sec < 0 ||
	    curtime.tv_sec > acpi_battery_get_info_expire());
}