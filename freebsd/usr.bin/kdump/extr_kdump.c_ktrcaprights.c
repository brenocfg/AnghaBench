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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysdecode_cap_rights (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ktrcaprights(cap_rights_t *rightsp)
{

	printf("cap_rights_t ");
	sysdecode_cap_rights(stdout, rightsp);
	printf("\n");
}