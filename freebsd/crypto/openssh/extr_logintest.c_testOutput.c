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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  testLineName (char*) ; 

int
testOutput()
{
	printf("**\n** Testing linename functions\n**\n");
	testLineName("/dev/pts/1");
	testLineName("pts/1");
	testLineName("pts/999");
	testLineName("/dev/ttyp00");
	testLineName("ttyp00");

	return 1;
}