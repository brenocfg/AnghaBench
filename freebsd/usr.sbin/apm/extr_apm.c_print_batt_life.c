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
typedef  int u_int ;

/* Variables and functions */
 int APM_UNKNOWN ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_batt_life(u_int batt_life)
{
	printf("Remaining battery life: ");
	if (batt_life == APM_UNKNOWN)
		printf("unknown\n");
	else if (batt_life <= 100)
		printf("%d%%\n", batt_life);
	else
		printf("invalid value (0x%x)\n", batt_life);
}