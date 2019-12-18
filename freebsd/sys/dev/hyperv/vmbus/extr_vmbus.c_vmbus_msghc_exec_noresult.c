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
typedef  scalar_t__ uint64_t ;
struct hypercall_postmsg_in {int dummy; } ;
struct vmbus_msghc {struct hypercall_postmsg_in mh_inprm_save; int /*<<< orphan*/  mh_xact; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_HARDCLOCK ; 
 int EIO ; 
 int HC_RETRY_MAX ; 
 int /*<<< orphan*/  HYPERCALL_POSTMSGIN_SIZE ; 
 scalar_t__ HYPERCALL_STATUS_SUCCESS ; 
 int SBT_1MS ; 
 int SBT_1S ; 
 scalar_t__ hypercall_post_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct hypercall_postmsg_in*,struct hypercall_postmsg_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hypercall_postmsg_in* vmbus_xact_req_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_xact_req_paddr (int /*<<< orphan*/ ) ; 

int
vmbus_msghc_exec_noresult(struct vmbus_msghc *mh)
{
	sbintime_t time = SBT_1MS;
	struct hypercall_postmsg_in *inprm;
	bus_addr_t inprm_paddr;
	int i;

	inprm = vmbus_xact_req_data(mh->mh_xact);
	inprm_paddr = vmbus_xact_req_paddr(mh->mh_xact);

	/*
	 * Save the input parameter so that we could restore the input
	 * parameter if the Hypercall failed.
	 *
	 * XXX
	 * Is this really necessary?!  i.e. Will the Hypercall ever
	 * overwrite the input parameter?
	 */
	memcpy(&mh->mh_inprm_save, inprm, HYPERCALL_POSTMSGIN_SIZE);

	/*
	 * In order to cope with transient failures, e.g. insufficient
	 * resources on host side, we retry the post message Hypercall
	 * several times.  20 retries seem sufficient.
	 */
#define HC_RETRY_MAX	20

	for (i = 0; i < HC_RETRY_MAX; ++i) {
		uint64_t status;

		status = hypercall_post_message(inprm_paddr);
		if (status == HYPERCALL_STATUS_SUCCESS)
			return 0;

		pause_sbt("hcpmsg", time, 0, C_HARDCLOCK);
		if (time < SBT_1S * 2)
			time *= 2;

		/* Restore input parameter and try again */
		memcpy(inprm, &mh->mh_inprm_save, HYPERCALL_POSTMSGIN_SIZE);
	}

#undef HC_RETRY_MAX

	return EIO;
}