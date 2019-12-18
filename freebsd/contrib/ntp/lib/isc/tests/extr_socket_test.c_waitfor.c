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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ done; } ;
typedef  TYPE_1__ completion_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_FAILURE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  isc__taskmgr_dispatch (int /*<<< orphan*/ ) ; 
 scalar_t__ isc__taskmgr_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_test_nap (int) ; 
 int /*<<< orphan*/  taskmgr ; 

__attribute__((used)) static isc_result_t
waitfor(completion_t *completion) {
	int i = 0;
	while (!completion->done && i++ < 5000) {
#ifndef ISC_PLATFORM_USETHREADS
		while (isc__taskmgr_ready(taskmgr))
			isc__taskmgr_dispatch(taskmgr);
#endif
		isc_test_nap(1000);
	}
	if (completion->done)
		return (ISC_R_SUCCESS);
	return (ISC_R_FAILURE);
}