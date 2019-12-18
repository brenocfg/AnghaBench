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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {char* rt_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* test ; 
 int test_acknowleged ; 
 int test_index ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vprint_status(const char *status, const char *fmt, va_list ap)
{

	printf("%s %d", status, test_index);
	if (test->rt_name)
		printf(" - %s", test->rt_name);
	if (fmt) {
		printf(" # ");
		vprintf(fmt, ap);
	}
	printf("\n");
	test_acknowleged = 1;
}