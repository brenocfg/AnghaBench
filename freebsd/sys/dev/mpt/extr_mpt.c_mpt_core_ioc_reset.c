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
struct mpt_softc {int /*<<< orphan*/  request_pending_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_IOCSTATUS_INVALID_STATE ; 
 int /*<<< orphan*/  mpt_complete_request_chain (struct mpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpt_core_ioc_reset(struct mpt_softc *mpt, int type)
{

	/*
	 * Complete all pending requests with a status
	 * appropriate for an IOC reset.
	 */
	mpt_complete_request_chain(mpt, &mpt->request_pending_list,
				   MPI_IOCSTATUS_INVALID_STATE);
}