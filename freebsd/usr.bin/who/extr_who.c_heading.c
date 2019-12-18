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
 scalar_t__ Tflag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ uflag ; 

__attribute__((used)) static void
heading(void)
{

	printf("%-16s ", "NAME");
	if (Tflag)
		printf("S ");
	printf("%-12s %-12s ", "LINE", "TIME");
	if (uflag)
		printf("IDLE  ");
	printf("%-16s\n", "FROM");
}