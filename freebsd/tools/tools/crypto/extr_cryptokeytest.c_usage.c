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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(const char* cmd)
{
	printf("usage: %s [-d dev] [-v] [count]\n", cmd);
	printf("count is the number of bignum ops to do\n");
	printf("\n");
	printf("-d use specific device\n");
	printf("-v be verbose\n");
	exit(-1);
}