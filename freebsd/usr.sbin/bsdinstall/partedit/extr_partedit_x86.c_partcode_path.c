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
partcode_path(const char *part_type, const char *fs_type)
{

	if (strcmp(part_type, "GPT") == 0 && strcmp(x86_bootmethod(), "UEFI") != 0) {
		if (strcmp(fs_type, "zfs") == 0)
			return ("/boot/gptzfsboot");
		else
			return ("/boot/gptboot");
	}
	
	/* No partcode except for non-UEFI GPT */
	return (NULL);
}