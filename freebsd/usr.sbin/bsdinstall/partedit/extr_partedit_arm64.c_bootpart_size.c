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
 size_t EFI_BOOTPART_SIZE ; 
 scalar_t__ strcmp (char const*,char*) ; 

size_t
bootpart_size(const char *scheme)
{

	/* We only support GPT with EFI */
	if (strcmp(scheme, "GPT") != 0)
		return (0);

	return (EFI_BOOTPART_SIZE);
}