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
 unsigned int nitems (char const**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reject_option(const char *option)
{
	static const char *reject[] = {
		"acpi.rsdp",
	};
	unsigned int i;

	for (i = 0; i < nitems(reject); i++)
		if (strncmp(option, reject[i], strlen(reject[i])) == 0)
			return (true);

	return (false);
}