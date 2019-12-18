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
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int PF_OPT_SHOWALL ; 
 int /*<<< orphan*/  classes ; 
 int fingerprint_count ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_name_list (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sort_name_list (int,int /*<<< orphan*/ *) ; 

void
pfctl_show_fingerprints(int opts)
{
	if (LIST_FIRST(&classes) != NULL) {
		if (opts & PF_OPT_SHOWALL) {
			pfctl_print_title("OS FINGERPRINTS:");
			printf("%u fingerprints loaded\n", fingerprint_count);
		} else {
			printf("Class\tVersion\tSubtype(subversion)\n");
			printf("-----\t-------\t-------------------\n");
			sort_name_list(opts, &classes);
			print_name_list(opts, &classes, "");
		}
	}
}