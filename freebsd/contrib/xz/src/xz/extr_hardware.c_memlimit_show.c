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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,...) ; 
 scalar_t__ round_up_to_mib (scalar_t__) ; 
 char* uint64_to_str (scalar_t__,int) ; 

__attribute__((used)) static void
memlimit_show(const char *str, uint64_t value)
{
	// The memory usage limit is considered to be disabled if value
	// is 0 or UINT64_MAX. This might get a bit more complex once there
	// is threading support. See the comment in hardware_memlimit_get().
	if (value == 0 || value == UINT64_MAX)
		printf("%s %s\n", str, _("Disabled"));
	else
		printf("%s %s MiB (%s B)\n", str,
				uint64_to_str(round_up_to_mib(value), 0),
				uint64_to_str(value, 1));

	return;
}