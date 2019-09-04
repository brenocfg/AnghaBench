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
struct clar_report {scalar_t__ status; struct clar_error* errors; struct clar_report* next; } ;
struct clar_error {struct clar_error* next; } ;
struct TYPE_2__ {struct clar_report* reports; } ;

/* Variables and functions */
 scalar_t__ CL_TEST_FAILURE ; 
 TYPE_1__ _clar ; 
 int /*<<< orphan*/  clar_print_error (int /*<<< orphan*/ ,struct clar_report*,struct clar_error*) ; 

__attribute__((used)) static void
clar_report_all(void)
{
	struct clar_report *report;
	struct clar_error *error;
	int i = 1;

	for (report = _clar.reports; report; report = report->next) {
		if (report->status != CL_TEST_FAILURE)
			continue;

		for (error = report->errors; error; error = error->next)
			clar_print_error(i++, report, error);
	}
}