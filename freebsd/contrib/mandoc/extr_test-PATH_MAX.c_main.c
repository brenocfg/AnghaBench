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
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  printf (char*,long) ; 

int
main(void)
{
	printf("PATH_MAX is defined to be %ld\n", (long)PATH_MAX);
	return 0;
}