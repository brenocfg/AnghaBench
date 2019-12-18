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
 int CMD_ERROR ; 
 int CMD_OK ; 
 char* command_errmsg ; 
 char* strerror (int) ; 
 int zfs_list (char*) ; 

__attribute__((used)) static int
command_lszfs(int argc, char *argv[])
{
	int err;

	if (argc != 2) {
		command_errmsg = "a single dataset must be supplied";
		return (CMD_ERROR);
	}

	err = zfs_list(argv[1]);
	if (err != 0) {
		command_errmsg = strerror(err);
		return (CMD_ERROR);
	}
	return (CMD_OK);
}