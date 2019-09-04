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
struct clar_explicit {size_t suite_idx; int /*<<< orphan*/ * filter; struct clar_explicit* next; } ;
struct TYPE_2__ {int total_errors; struct clar_explicit* explicit; } ;

/* Variables and functions */
 TYPE_1__ _clar ; 
 size_t _clar_suite_count ; 
 int /*<<< orphan*/ * _clar_suites ; 
 int /*<<< orphan*/  clar_run_suite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
clar_test_run(void)
{
	size_t i;
	struct clar_explicit *explicit;

	if (_clar.explicit) {
		for (explicit = _clar.explicit; explicit; explicit = explicit->next)
			clar_run_suite(&_clar_suites[explicit->suite_idx], explicit->filter);
	} else {
		for (i = 0; i < _clar_suite_count; ++i)
			clar_run_suite(&_clar_suites[i], NULL);
	}

	return _clar.total_errors;
}