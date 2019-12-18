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

/* Variables and functions */
 int /*<<< orphan*/  ACPIAC ; 
 int /*<<< orphan*/  APMDEV ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PMUAC ; 
 int /*<<< orphan*/  SRC_UNKNOWN ; 
 scalar_t__ ac_acpi_devd ; 
 scalar_t__ ac_apm ; 
 scalar_t__ ac_none ; 
 scalar_t__ ac_sysctl ; 
 int /*<<< orphan*/  acline_mib ; 
 int acline_mib_len ; 
 scalar_t__ acline_mode ; 
 scalar_t__ acline_mode_user ; 
 int /*<<< orphan*/  acline_status ; 
 int /*<<< orphan*/  apm_fd ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlnametomib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
acline_init(void)
{
	int skip_source_check;

	acline_mib_len = 4;
	acline_status = SRC_UNKNOWN;
	skip_source_check = (acline_mode_user == ac_none ||
			     acline_mode_user == ac_acpi_devd);

	if ((skip_source_check || acline_mode_user == ac_sysctl) &&
	    sysctlnametomib(ACPIAC, acline_mib, &acline_mib_len) == 0) {
		acline_mode = ac_sysctl;
		if (vflag)
			warnx("using sysctl for AC line status");
#ifdef __powerpc__
	} else if ((skip_source_check || acline_mode_user == ac_sysctl) &&
		   sysctlnametomib(PMUAC, acline_mib, &acline_mib_len) == 0) {
		acline_mode = ac_sysctl;
		if (vflag)
			warnx("using sysctl for AC line status");
#endif
#ifdef USE_APM
	} else if ((skip_source_check || acline_mode_user == ac_apm) &&
		   (apm_fd = open(APMDEV, O_RDONLY)) >= 0) {
		if (vflag)
			warnx("using APM for AC line status");
		acline_mode = ac_apm;
#endif
	} else {
		warnx("unable to determine AC line status");
		acline_mode = ac_none;
	}
}