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
 char* active_test_name ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,char*,char*,char*) ; 
 char* subtest_info ; 
 int test_number ; 

void
test_info(char *s, size_t len)
{
	snprintf(s, len, "In test %u: \"%s\"%s%s\n", test_number,
	    active_test_name == NULL ? "<none>" : active_test_name,
	    *subtest_info != '\0' ? " - " : "", subtest_info);
}