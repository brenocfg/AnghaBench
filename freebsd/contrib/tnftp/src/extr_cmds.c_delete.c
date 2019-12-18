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
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ command (char*,char*) ; 
 int dirchange ; 

void
delete(int argc, char *argv[])
{

	if (argc == 0 || argc > 2 ||
	    (argc == 1 && !another(&argc, &argv, "remote-file"))) {
		UPRINTF("usage: %s remote-file\n", argv[0]);
		code = -1;
		return;
	}
	if (command("DELE %s", argv[1]) == COMPLETE)
		dirchange = 1;
}