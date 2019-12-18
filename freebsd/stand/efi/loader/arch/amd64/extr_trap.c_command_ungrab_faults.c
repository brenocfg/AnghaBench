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
 int CMD_OK ; 
 int /*<<< orphan*/  efi_unredirect_exceptions () ; 

__attribute__((used)) static int
command_ungrab_faults(int argc, char *argv[])
{

	efi_unredirect_exceptions();
	return (CMD_OK);
}