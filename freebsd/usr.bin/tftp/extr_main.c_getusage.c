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
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
getusage(char *s)
{

	printf("usage: %s file [localname]\n", s);
	printf("       %s [host:]file [localname]\n", s);
	printf("       %s [host1:]file1 [host2:]file2 ... [hostN:]fileN\n", s);
}