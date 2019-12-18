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
 int getinflight () ; 
 int getopenfiles () ; 
 int /*<<< orphan*/  test ; 
 int /*<<< orphan*/  trigger_gc () ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
test_sysctls(int before_inflight, int before_openfiles)
{
	int after_inflight, after_openfiles;

	trigger_gc();
	after_inflight = getinflight();
	if (after_inflight != before_inflight)
		warnx("%s: before inflight: %d, after inflight: %d",
		    test, before_inflight, after_inflight);

	after_openfiles = getopenfiles();
	if (after_openfiles != before_openfiles)
		warnx("%s: before: %d, after: %d", test, before_openfiles,
		    after_openfiles);
}