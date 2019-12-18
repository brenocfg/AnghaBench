#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmcap ;
struct efi_tmcap {long tc_res; scalar_t__ tc_stz; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCKF_SETTIME_NO_ADJ ; 
 int /*<<< orphan*/  bzero (struct efi_tmcap*,int) ; 
 int /*<<< orphan*/  clock_register_flags (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_schedule (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int efi_get_time_capabilities (struct efi_tmcap*) ; 
 TYPE_1__ efirtc_resadj ; 
 scalar_t__ efirtc_zeroes_subseconds ; 
 scalar_t__ ns_per_s ; 
 long ns_per_us ; 
 long us_per_s ; 

__attribute__((used)) static int
efirtc_attach(device_t dev)
{
	struct efi_tmcap tmcap;
	long res;
	int error;

	bzero(&tmcap, sizeof(tmcap));
	if ((error = efi_get_time_capabilities(&tmcap)) != 0) {
		device_printf(dev, "cannot get EFI time capabilities");
		return (error);
	}

	/* Translate resolution in Hz to tick length in usec. */
	if (tmcap.tc_res == 0)
		res = us_per_s; /* 0 is insane, assume 1 Hz. */
	else if (tmcap.tc_res > us_per_s)
		res = 1; /* 1us is the best we can represent */
	else
		res = us_per_s / tmcap.tc_res;

	/* Clock rounding adjustment is 1/2 of resolution, in nsec. */
	efirtc_resadj.tv_nsec = (res * ns_per_us) / 2;

	/* Does the clock zero the subseconds when time is set? */
	efirtc_zeroes_subseconds = tmcap.tc_stz;

	/*
	 * Register.  If the clock zeroes out the subseconds when it's set,
	 * schedule the SetTime calls to happen just before top-of-second.
	 */
	clock_register_flags(dev, res, CLOCKF_SETTIME_NO_ADJ);
	if (efirtc_zeroes_subseconds)
		clock_schedule(dev, ns_per_s - ns_per_us);

	return (0);
}