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
struct clar_report {struct clar_report* next; } ;
struct clar_explicit {struct clar_explicit* next; } ;
struct TYPE_2__ {struct clar_report* summary_filename; struct clar_report* reports; struct clar_report* explicit; int /*<<< orphan*/  summary; scalar_t__ write_summary; int /*<<< orphan*/  total_errors; int /*<<< orphan*/  tests_ran; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 
 scalar_t__ _clar_suite_count ; 
 int /*<<< orphan*/  clar_print_onabort (char*) ; 
 int /*<<< orphan*/  clar_print_shutdown (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ clar_summary_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_unsandbox () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct clar_report*) ; 

void
clar_test_shutdown(void)
{
	struct clar_explicit *explicit, *explicit_next;
	struct clar_report *report, *report_next;

	clar_print_shutdown(
		_clar.tests_ran,
		(int)_clar_suite_count,
		_clar.total_errors
	);

	clar_unsandbox();

	if (_clar.write_summary && clar_summary_shutdown(_clar.summary) < 0) {
		clar_print_onabort("Failed to write the summary file\n");
		exit(-1);
	}

	for (explicit = _clar.explicit; explicit; explicit = explicit_next) {
		explicit_next = explicit->next;
		free(explicit);
	}

	for (report = _clar.reports; report; report = report_next) {
		report_next = report->next;
		free(report);
	}

	free(_clar.summary_filename);
}