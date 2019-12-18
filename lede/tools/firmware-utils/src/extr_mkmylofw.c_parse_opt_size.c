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
 int /*<<< orphan*/  dbgmsg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  flash_size ; 
 scalar_t__ required_arg (char,char*) ; 
 scalar_t__ str2u32 (char*,int /*<<< orphan*/ *) ; 

int
parse_opt_size(char ch, char *arg)
{
	if (required_arg(ch, arg)) {
		goto err_out;
	}

	if (str2u32(arg, &flash_size) != 0) {
		errmsg(0,"invalid flash size: %s", arg);
		goto err_out;
	}

	dbgmsg(1, "flash size set to %d bytes", flash_size);

	return 0;

err_out:
	return -1;
}