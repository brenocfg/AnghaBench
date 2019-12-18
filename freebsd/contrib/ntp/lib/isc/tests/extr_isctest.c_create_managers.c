#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  cleanup_managers () ; 
 int isc_os_ncpus () ; 
 int /*<<< orphan*/  isc_socketmgr_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_taskmgr_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_timermgr_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mctx ; 
 int ncpus ; 
 int /*<<< orphan*/  socketmgr ; 
 int /*<<< orphan*/  taskmgr ; 
 int /*<<< orphan*/  timermgr ; 

__attribute__((used)) static isc_result_t
create_managers() {
	isc_result_t result;
#ifdef ISC_PLATFORM_USETHREADS
	ncpus = isc_os_ncpus();
#else
	ncpus = 1;
#endif

	CHECK(isc_taskmgr_create(mctx, ncpus, 0, &taskmgr));
	CHECK(isc_timermgr_create(mctx, &timermgr));
	CHECK(isc_socketmgr_create(mctx, &socketmgr));
	return (ISC_R_SUCCESS);

  cleanup:
	cleanup_managers();
	return (result);
}