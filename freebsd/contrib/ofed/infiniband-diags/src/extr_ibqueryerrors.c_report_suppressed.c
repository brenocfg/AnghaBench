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
 char* mad_field_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sup_total ; 
 int /*<<< orphan*/ * suppressed_fields ; 

__attribute__((used)) static void report_suppressed(void)
{
	int i = 0;
	printf("## Suppressed:");
	for (i = 0; i < sup_total; i++)
		printf(" %s", mad_field_name(suppressed_fields[i]));
	printf("\n");
}