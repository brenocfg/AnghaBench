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
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  command (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
sizecmd(int argc, char **argv)
{

	if (argc < 2 && !another(&argc, &argv, "filename")) {
		printf("usage: %s filename\n", argv[0]);
		code = -1;
		return;
	}
	command("SIZE %s", argv[1]);
}