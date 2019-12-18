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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int /*<<< orphan*/  boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  boothowto ; 

int
ofw_parse_bootargs(void)
{
	phandle_t chosen;
	char buf[2048];		/* early stack supposedly big enough */
	int err;

	chosen = OF_finddevice("/chosen");
	if (chosen == -1)
		return (chosen);

	if ((err = OF_getprop(chosen, "bootargs", buf, sizeof(buf))) != -1) {
		boothowto |= boot_parse_cmdline(buf);
		return (0);
	}

	return (err);
}