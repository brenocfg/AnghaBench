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
typedef  enum mandoc_os { ____Placeholder_mandoc_os } mandoc_os ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 

int
arch_valid(const char *arch, enum mandoc_os os)
{
	const char *openbsd_arch[] = {
		"alpha", "amd64", "arm64", "armv7", "hppa", "i386",
		"landisk", "loongson", "luna88k", "macppc", "mips64",
		"octeon", "sgi", "sparc64", NULL
	};
	const char *netbsd_arch[] = {
		"acorn26", "acorn32", "algor", "alpha", "amiga",
		"arc", "atari",
		"bebox", "cats", "cesfic", "cobalt", "dreamcast",
		"emips", "evbarm", "evbmips", "evbppc", "evbsh3", "evbsh5",
		"hp300", "hpcarm", "hpcmips", "hpcsh", "hppa",
		"i386", "ibmnws", "luna68k",
		"mac68k", "macppc", "mipsco", "mmeye", "mvme68k", "mvmeppc",
		"netwinder", "news68k", "newsmips", "next68k",
		"pc532", "playstation2", "pmax", "pmppc", "prep",
		"sandpoint", "sbmips", "sgimips", "shark",
		"sparc", "sparc64", "sun2", "sun3",
		"vax", "walnut", "x68k", "x86", "x86_64", "xen", NULL
	};
	const char **arches[] = { NULL, netbsd_arch, openbsd_arch };
	const char **arch_p;

	if ((arch_p = arches[os]) == NULL)
		return 1;
	for (; *arch_p != NULL; arch_p++)
		if (strcmp(*arch_p, arch) == 0)
			return 1;
	return 0;
}