#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {scalar_t__ maximum_size; int /*<<< orphan*/  versions; int /*<<< orphan*/ * name; int /*<<< orphan*/ * stream; } ;
struct TYPE_5__ {TYPE_1__ file; } ;
typedef  TYPE_2__ isc_logdestination_t ;
typedef  int /*<<< orphan*/  isc_logconfig_t ;
typedef  scalar_t__ isc_boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LOG_DYNAMIC ; 
 int /*<<< orphan*/  ISC_LOG_ROLLNEVER ; 
 int /*<<< orphan*/  ISC_LOG_TOFILEDESC ; 
 int /*<<< orphan*/  ISC_MEM_DEBUGRECORD ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  categories ; 
 int /*<<< orphan*/  create_managers () ; 
 int /*<<< orphan*/  ectx ; 
 int /*<<< orphan*/  hash_active ; 
 int /*<<< orphan*/  isc_entropy_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_hash_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_log_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_log_createchannel (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_log_registercategories (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_log_setcontext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_log_usechannel (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_debugging ; 
 int isc_os_ncpus () ; 
 int /*<<< orphan*/  isc_test_end () ; 
 int /*<<< orphan*/  lctx ; 
 int /*<<< orphan*/  mctx ; 
 int ncpus ; 

isc_result_t
isc_test_begin(FILE *logfile, isc_boolean_t start_managers) {
	isc_result_t result;

	isc_mem_debugging |= ISC_MEM_DEBUGRECORD;
	CHECK(isc_mem_create(0, 0, &mctx));
	CHECK(isc_entropy_create(mctx, &ectx));

	CHECK(isc_hash_create(mctx, ectx, 255));
	hash_active = ISC_TRUE;

	if (logfile != NULL) {
		isc_logdestination_t destination;
		isc_logconfig_t *logconfig = NULL;

		CHECK(isc_log_create(mctx, &lctx, &logconfig));
		isc_log_registercategories(lctx, categories);
		isc_log_setcontext(lctx);

		destination.file.stream = logfile;
		destination.file.name = NULL;
		destination.file.versions = ISC_LOG_ROLLNEVER;
		destination.file.maximum_size = 0;
		CHECK(isc_log_createchannel(logconfig, "stderr",
					    ISC_LOG_TOFILEDESC,
					    ISC_LOG_DYNAMIC,
					    &destination, 0));
		CHECK(isc_log_usechannel(logconfig, "stderr", NULL, NULL));
	}

#ifdef ISC_PLATFORM_USETHREADS
	ncpus = isc_os_ncpus();
#else
	ncpus = 1;
#endif

	if (start_managers)
		CHECK(create_managers());

	return (ISC_R_SUCCESS);

  cleanup:
	isc_test_end();
	return (result);
}