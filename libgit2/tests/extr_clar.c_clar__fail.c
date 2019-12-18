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
struct clar_error {char const* file; size_t line_number; char const* error_msg; int /*<<< orphan*/  description; struct clar_error* next; } ;
struct TYPE_4__ {TYPE_1__* last_report; int /*<<< orphan*/  total_errors; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; struct clar_error* last_error; struct clar_error* errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_TEST_FAILURE ; 
 TYPE_2__ _clar ; 
 int /*<<< orphan*/  abort_test () ; 
 struct clar_error* calloc (int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

void clar__fail(
	const char *file,
	size_t line,
	const char *error_msg,
	const char *description,
	int should_abort)
{
	struct clar_error *error = calloc(1, sizeof(struct clar_error));

	if (_clar.last_report->errors == NULL)
		_clar.last_report->errors = error;

	if (_clar.last_report->last_error != NULL)
		_clar.last_report->last_error->next = error;

	_clar.last_report->last_error = error;

	error->file = file;
	error->line_number = line;
	error->error_msg = error_msg;

	if (description != NULL)
		error->description = strdup(description);

	_clar.total_errors++;
	_clar.last_report->status = CL_TEST_FAILURE;

	if (should_abort)
		abort_test();
}