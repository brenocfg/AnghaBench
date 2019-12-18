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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* VM_MAX_WIRED ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  vm_max_wired_sysctl (int /*<<< orphan*/ *,scalar_t__*) ; 

void
restore_vm_max_wired(void)
{
	FILE *fp;
	u_long saved_max_wired;

	fp = fopen(VM_MAX_WIRED, "r");
	if (fp == NULL) {
		perror("fopen failed\n");
		return;
	}

	if (fscanf(fp, "%lu", &saved_max_wired) != 1) {
		perror("fscanf failed\n");
		fclose(fp);
		return;
	}

	fclose(fp);
	printf("old value in %s: %lu\n", VM_MAX_WIRED, saved_max_wired);

	if (saved_max_wired == 0) /* This will cripple the test host */
		return;

	vm_max_wired_sysctl(NULL, &saved_max_wired);
}