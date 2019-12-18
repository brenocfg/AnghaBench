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
typedef  int /*<<< orphan*/  var ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int boot_parse_arg (char*) ; 
 int /*<<< orphan*/  cpy16to8 (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
parse_args(int argc, CHAR16 *argv[])
{
	int i, j, howto;
	bool vargood;
	char var[128];

	/*
	 * Parse the args to set the console settings, etc
	 * boot1.efi passes these in, if it can read /boot.config or /boot/config
	 * or iPXE may be setup to pass these in. Or the optional argument in the
	 * boot environment was used to pass these arguments in (in which case
	 * neither /boot.config nor /boot/config are consulted).
	 *
	 * Loop through the args, and for each one that contains an '=' that is
	 * not the first character, add it to the environment.  This allows
	 * loader and kernel env vars to be passed on the command line.  Convert
	 * args from UCS-2 to ASCII (16 to 8 bit) as they are copied (though this
	 * method is flawed for non-ASCII characters).
	 */
	howto = 0;
	for (i = 1; i < argc; i++) {
		cpy16to8(argv[i], var, sizeof(var));
		howto |= boot_parse_arg(var);
	}

	return (howto);
}