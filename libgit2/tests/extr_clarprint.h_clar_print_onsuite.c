#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ report_suite_names; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void clar_print_onsuite(const char *suite_name, int suite_index)
{
	if (_clar.report_suite_names)
		printf("\n%s", suite_name);

	(void)suite_index;
}