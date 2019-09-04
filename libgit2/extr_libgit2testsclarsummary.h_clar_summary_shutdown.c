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
struct clar_summary {char* filename; int /*<<< orphan*/  fp; } ;
struct clar_report {char* suite; struct clar_report* next; int /*<<< orphan*/  test; struct clar_error* errors; } ;
struct clar_error {struct clar_error* next; int /*<<< orphan*/  description; int /*<<< orphan*/  error_msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_errors; int /*<<< orphan*/  tests_ran; struct clar_report* reports; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 
 scalar_t__ clar_summary_close_tag (struct clar_summary*,char*,int) ; 
 scalar_t__ clar_summary_failure (struct clar_summary*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_summary_testcase (struct clar_summary*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ clar_summary_testsuite (struct clar_summary*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clar_summary_testsuites (struct clar_summary*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct clar_summary*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int clar_summary_shutdown(struct clar_summary *summary)
{
	struct clar_report *report;
	const char *last_suite = NULL;

	if (clar_summary_testsuites(summary) < 0)
		goto on_error;

	report = _clar.reports;
	while (report != NULL) {
		struct clar_error *error = report->errors;

		if (last_suite == NULL || strcmp(last_suite, report->suite) != 0) {
			if (clar_summary_testsuite(summary, 0, report->suite, "",
			    time(NULL), 0, _clar.tests_ran, _clar.total_errors, 0) < 0)
				goto on_error;
		}

		last_suite = report->suite;

		clar_summary_testcase(summary, report->test, "what", 0);

		while (error != NULL) {
			if (clar_summary_failure(summary, "assert",
			    error->error_msg, error->description) < 0)
				goto on_error;

			error = error->next;
		}

		if (clar_summary_close_tag(summary, "testcase", 2) < 0)
			goto on_error;

		report = report->next;

		if (!report || strcmp(last_suite, report->suite) != 0) {
			if (clar_summary_close_tag(summary, "testsuite", 1) < 0)
				goto on_error;
		}
	}

	if (clar_summary_close_tag(summary, "testsuites", 0) < 0 ||
	    fclose(summary->fp) != 0)
		goto on_error;

	printf("written summary file to %s\n", summary->filename);

	free(summary);
	return 0;

on_error:
	fclose(summary->fp);
	free(summary);
	return -1;
}