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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  command (char*,char*,char*) ; 

void
do_chmod(int argc, char *argv[])
{

	if (argc == 0 || (argc == 1 && !another(&argc, &argv, "mode")))
		goto usage;
	if ((argc < 3 && !another(&argc, &argv, "remote-file")) || argc > 3) {
 usage:
		UPRINTF("usage: %s mode remote-file\n", argv[0]);
		code = -1;
		return;
	}
	(void)command("SITE CHMOD %s %s", argv[1], argv[2]);
}