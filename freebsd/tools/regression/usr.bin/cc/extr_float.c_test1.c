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
 int /*<<< orphan*/  failures ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,char const*) ; 
 int testnum ; 

__attribute__((used)) static void
test1(const char *testdesc, int pass, int skip)
{

	testnum++;
	printf("%sok %d - %s%s\n", pass || skip ? "" : "not ", testnum, 
	    skip ? "(SKIPPED) " : "", testdesc);
	if (!pass && !skip)
		failures++;
}