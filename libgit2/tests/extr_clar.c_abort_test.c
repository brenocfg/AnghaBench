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
struct TYPE_2__ {int /*<<< orphan*/  trampoline; int /*<<< orphan*/  last_report; int /*<<< orphan*/  trampoline_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_TRACE__TEST__LONGJMP ; 
 TYPE_1__ _clar ; 
 int /*<<< orphan*/  clar_print_onabort (char*) ; 
 int /*<<< orphan*/  clar_report_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void abort_test(void)
{
	if (!_clar.trampoline_enabled) {
		clar_print_onabort(
				"Fatal error: a cleanup method raised an exception.");
		clar_report_errors(_clar.last_report);
		exit(-1);
	}

	CL_TRACE(CL_TRACE__TEST__LONGJMP);
	longjmp(_clar.trampoline, -1);
}