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
 scalar_t__ strcmp (char const*,char*) ; 
 char const* x86_bootmethod () ; 

const char *
bootcode_path(const char *part_type)
{

	if (strcmp(x86_bootmethod(), "UEFI") == 0)
		return (NULL);

	if (strcmp(part_type, "GPT") == 0)
		return ("/boot/pmbr");
	if (strcmp(part_type, "MBR") == 0)
		return ("/boot/mbr");
	if (strcmp(part_type, "BSD") == 0)
		return ("/boot/boot");

	return (NULL);
}