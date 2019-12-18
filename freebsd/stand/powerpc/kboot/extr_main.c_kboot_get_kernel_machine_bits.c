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
typedef  int /*<<< orphan*/  utsname ;
typedef  int uint8_t ;
struct old_utsname {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int host_uname (struct old_utsname*) ; 
 int /*<<< orphan*/  memset (struct old_utsname*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

uint8_t
kboot_get_kernel_machine_bits(void)
{
	static uint8_t bits = 0;
	struct old_utsname utsname;
	int ret;

	if (bits == 0) {
		/* Default is 32-bit kernel */
		bits = 32;

		/* Try to get system type */
		memset(&utsname, 0, sizeof(utsname));
		ret = host_uname(&utsname);
		if (ret == 0) {
			if (strcmp(utsname.machine, "ppc64") == 0)
				bits = 64;
			else if (strcmp(utsname.machine, "ppc64le") == 0)
				bits = 64;
		}
	}

	return (bits);
}