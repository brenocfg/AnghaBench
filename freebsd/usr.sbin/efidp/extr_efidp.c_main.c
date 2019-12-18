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
 int /*<<< orphan*/  efi_to_unix () ; 
 scalar_t__ flag_efi ; 
 scalar_t__ flag_format ; 
 scalar_t__ flag_parse ; 
 scalar_t__ flag_unix ; 
 int /*<<< orphan*/  format () ; 
 int /*<<< orphan*/  parse () ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  unix_to_efi () ; 

int
main(int argc, char **argv)
{

	parse_args(argc, argv);
	if (flag_unix)
		efi_to_unix();
	else if (flag_efi)
		unix_to_efi();
	else if (flag_format)
		format();
	else if (flag_parse)
		parse();
}