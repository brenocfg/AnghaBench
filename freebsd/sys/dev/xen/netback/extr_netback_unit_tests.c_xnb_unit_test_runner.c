#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* setup ) () ;int /*<<< orphan*/  (* teardown ) () ;int /*<<< orphan*/  (* test ) (char*,size_t) ;} ;
typedef  TYPE_1__ test_fixture_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNCATF (char*,size_t,char*,int) ; 
 size_t strnlen (char*,size_t) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (char*,size_t) ; 
 int /*<<< orphan*/  stub3 () ; 

__attribute__((used)) static int
xnb_unit_test_runner(test_fixture_t const tests[], int ntests, char *buffer,
    		     size_t buflen)
{
	int i;
	int n_passes;
	int n_failures = 0;

	for (i = 0; i < ntests; i++) {
		int error = tests[i].setup();
		if (error != 0) {
			SNCATF(buffer, buflen,
			    "Setup failed for test idx %d\n", i);
			n_failures++;
		} else {
			size_t new_chars;

			tests[i].test(buffer, buflen);
			new_chars = strnlen(buffer, buflen);
			buffer += new_chars;
			buflen -= new_chars;

			if (new_chars > 0) {
				n_failures++;
			}
		}
		tests[i].teardown();
	}

	n_passes = ntests - n_failures;
	if (n_passes > 0) {
		SNCATF(buffer, buflen, "%d Tests Passed\n", n_passes);
	}
	if (n_failures > 0) {
		SNCATF(buffer, buflen, "%d Tests FAILED\n", n_failures);
	}

	return n_failures;
}