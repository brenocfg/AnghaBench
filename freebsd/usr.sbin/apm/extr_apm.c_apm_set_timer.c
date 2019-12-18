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
typedef  scalar_t__ time_t ;
struct tm {scalar_t__ tm_year; scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_sec; } ;
struct apm_bios_arg {int eax; int ecx; int edx; int esi; int edi; int /*<<< orphan*/  ebx; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  APMIO_BIOS ; 
 int APM_BIOS ; 
 int APM_RESUMETIMER ; 
 int /*<<< orphan*/  PMDV_APMBIOS ; 
 int /*<<< orphan*/  bzero (struct apm_bios_arg*,int) ; 
 scalar_t__ cmos_wall ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct tm* gmtime (scalar_t__*) ; 
 int int2bcd (scalar_t__) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct apm_bios_arg*) ; 
 struct tm* localtime (scalar_t__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apm_set_timer(int fd, int delta)
{
	time_t tmr;
	struct tm *tm;
	struct apm_bios_arg args;

	tmr = time(NULL) + delta;
	if (cmos_wall)
		tm = localtime(&tmr);
	else
		tm = gmtime(&tmr);
	bzero(&args, sizeof(args));
	args.eax = (APM_BIOS) << 8 | APM_RESUMETIMER;
	args.ebx = PMDV_APMBIOS;
	if (delta > 0) {
		args.ecx = (int2bcd(tm->tm_sec) << 8) | 0x02;
		args.edx = (int2bcd(tm->tm_hour) << 8) | int2bcd(tm->tm_min);
		args.esi = (int2bcd(tm->tm_mon + 1) << 8) | int2bcd(tm->tm_mday);
		args.edi = int2bcd(tm->tm_year + 1900);
	} else {
		args.ecx = 0x0000;
	}
	if (ioctl(fd, APMIO_BIOS, &args)) {
		err(1,"set resume timer");
	}
}