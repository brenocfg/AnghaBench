#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ia64_sal_os_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  proc_err; } ;
typedef  TYPE_1__ slidx_table_t ;
typedef  int /*<<< orphan*/  sal_log_processor_info_t ;
typedef  int /*<<< orphan*/  peidx_table_t ;
typedef  int /*<<< orphan*/  pal_bus_check_info_t ;
struct TYPE_7__ {scalar_t__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_check ; 
 int fatal_mca (char*) ; 
 scalar_t__ is_mca_global (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ia64_sal_os_state*) ; 
 int /*<<< orphan*/  mca_make_peidx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mca_make_slidx (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  peidx_check_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_err ; 
 int recover_from_processor_error (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ia64_sal_os_state*) ; 
 int slidx_count (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* slidx_first_entry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mca_try_to_recover(void *rec, struct ia64_sal_os_state *sos)
{
	int platform_err;
	int n_proc_err;
	slidx_table_t slidx;
	peidx_table_t peidx;
	pal_bus_check_info_t pbci;

	/* Make index of SAL error record */
	platform_err = mca_make_slidx(rec, &slidx);

	/* Count processor error sections */
	n_proc_err = slidx_count(&slidx, proc_err);

	 /* Now, OS can recover when there is one processor error section */
	if (n_proc_err > 1)
		return fatal_mca("Too Many Errors");
	else if (n_proc_err == 0)
		/* Weird SAL record ... We can't do anything */
		return fatal_mca("Weird SAL record");

	/* Make index of processor error section */
	mca_make_peidx((sal_log_processor_info_t*)
		slidx_first_entry(&slidx.proc_err)->hdr, &peidx);

	/* Extract Processor BUS_CHECK[0] */
	*((u64*)&pbci) = peidx_check_info(&peidx, bus_check, 0);

	/* Check whether MCA is global or not */
	if (is_mca_global(&peidx, &pbci, sos))
		return fatal_mca("global MCA");
	
	/* Try to recover a processor error */
	return recover_from_processor_error(platform_err, &slidx, &peidx,
					    &pbci, sos);
}