#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clar_func {int /*<<< orphan*/  name; int /*<<< orphan*/  (* ptr ) () ;} ;
struct TYPE_4__ {int trampoline_enabled; TYPE_1__* last_report; int /*<<< orphan*/  tests_ran; scalar_t__ report_errors_only; int /*<<< orphan*/ * local_cleanup_payload; int /*<<< orphan*/  (* local_cleanup ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  trampoline; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CL_TEST_NOTRUN ; 
 scalar_t__ CL_TEST_OK ; 
 int /*<<< orphan*/  CL_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_TRACE__TEST__BEGIN ; 
 int /*<<< orphan*/  CL_TRACE__TEST__END ; 
 int /*<<< orphan*/  CL_TRACE__TEST__RUN_BEGIN ; 
 int /*<<< orphan*/  CL_TRACE__TEST__RUN_END ; 
 TYPE_2__ _clar ; 
 int /*<<< orphan*/  clar_print_ontest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clar_report_errors (TYPE_1__*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 () ; 

__attribute__((used)) static void
clar_run_test(
	const struct clar_func *test,
	const struct clar_func *initialize,
	const struct clar_func *cleanup)
{
	_clar.trampoline_enabled = 1;

	CL_TRACE(CL_TRACE__TEST__BEGIN);

	if (setjmp(_clar.trampoline) == 0) {
		if (initialize->ptr != NULL)
			initialize->ptr();

		CL_TRACE(CL_TRACE__TEST__RUN_BEGIN);
		test->ptr();
		CL_TRACE(CL_TRACE__TEST__RUN_END);
	}

	_clar.trampoline_enabled = 0;

	if (_clar.last_report->status == CL_TEST_NOTRUN)
		_clar.last_report->status = CL_TEST_OK;

	if (_clar.local_cleanup != NULL)
		_clar.local_cleanup(_clar.local_cleanup_payload);

	if (cleanup->ptr != NULL)
		cleanup->ptr();

	CL_TRACE(CL_TRACE__TEST__END);

	_clar.tests_ran++;

	/* remove any local-set cleanup methods */
	_clar.local_cleanup = NULL;
	_clar.local_cleanup_payload = NULL;

	if (_clar.report_errors_only) {
		clar_report_errors(_clar.last_report);
	} else {
		clar_print_ontest(test->name, _clar.tests_ran, _clar.last_report->status);
	}
}