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
 char* IWN_DEFAULT_IF ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(void)
{
	printf("Usage: iwnstats [-h] [-i ifname]\n");
	printf("    -h:			Help\n");
	printf("    -i <ifname>:	Use ifname (default %s)\n",
	    IWN_DEFAULT_IF);
}