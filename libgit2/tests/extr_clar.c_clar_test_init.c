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
struct TYPE_2__ {int write_summary; int /*<<< orphan*/ * summary_filename; int /*<<< orphan*/  summary; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 
 scalar_t__ _clar_callback_count ; 
 scalar_t__ _clar_suite_count ; 
 int /*<<< orphan*/  clar_parse_args (int,char**) ; 
 int /*<<< orphan*/  clar_print_init (int,int,char*) ; 
 int /*<<< orphan*/  clar_print_onabort (char*) ; 
 scalar_t__ clar_sandbox () ; 
 int /*<<< orphan*/  clar_summary_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

void
clar_test_init(int argc, char **argv)
{
	clar_print_init(
		(int)_clar_callback_count,
		(int)_clar_suite_count,
		""
	);

	if ((_clar.summary_filename = getenv("CLAR_SUMMARY")) != NULL) {
		_clar.write_summary = 1;
		_clar.summary_filename = strdup(_clar.summary_filename);
	}

	if (argc > 1)
		clar_parse_args(argc, argv);

	if (_clar.write_summary &&
	    !(_clar.summary = clar_summary_init(_clar.summary_filename))) {
		clar_print_onabort("Failed to open the summary file\n");
		exit(-1);
	}

	if (clar_sandbox() < 0) {
		clar_print_onabort("Failed to sandbox the test runner.\n");
		exit(-1);
	}
}