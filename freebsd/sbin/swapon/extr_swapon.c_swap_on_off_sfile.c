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
#define  EBUSY 129 
#define  EINVAL 128 
 scalar_t__ Eflag ; 
 scalar_t__ SWAPON ; 
 int errno ; 
 int swapoff (char const*) ; 
 int swapon (char const*) ; 
 int swapon_trim (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 
 scalar_t__ which_prog ; 

__attribute__((used)) static const char *
swap_on_off_sfile(const char *name, int doingall)
{
	int error;

	if (which_prog == SWAPON)
		error = Eflag ? swapon_trim(name) : swapon(name);
	else /* SWAPOFF */
		error = swapoff(name);

	if (error == -1) {
		switch (errno) {
		case EBUSY:
			if (doingall == 0)
				warnx("%s: Device already in use", name);
			break;
		case EINVAL:
			if (which_prog == SWAPON)
				warnx("%s: NSWAPDEV limit reached", name);
			else if (doingall == 0)
				warn("%s", name);
			break;
		default:
			warn("%s", name);
			break;
		}
		return (NULL);
	}
	return (name);
}