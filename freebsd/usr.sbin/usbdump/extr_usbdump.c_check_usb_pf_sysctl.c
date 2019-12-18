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
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
check_usb_pf_sysctl(void)
{
	int error;
	int no_pf_val = 0;
	size_t no_pf_len = sizeof(int);

	/* check "hw.usb.no_pf" sysctl for 8- and 9- stable */

	error = sysctlbyname("hw.usb.no_pf", &no_pf_val,
	    &no_pf_len, NULL, 0);
	if (error == 0 && no_pf_val != 0) {
		warnx("The USB packet filter might be disabled.");
		warnx("See the \"hw.usb.no_pf\" sysctl for more information.");
	}
}