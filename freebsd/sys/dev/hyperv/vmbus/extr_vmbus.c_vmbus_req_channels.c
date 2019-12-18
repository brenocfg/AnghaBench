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
struct vmbus_softc {int dummy; } ;
struct vmbus_msghc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chm_type; } ;
struct vmbus_chanmsg_chrequest {TYPE_1__ chm_hdr; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VMBUS_CHANMSG_TYPE_CHREQUEST ; 
 struct vmbus_chanmsg_chrequest* vmbus_msghc_dataptr (struct vmbus_msghc*) ; 
 int vmbus_msghc_exec_noresult (struct vmbus_msghc*) ; 
 struct vmbus_msghc* vmbus_msghc_get (struct vmbus_softc*,int) ; 
 int /*<<< orphan*/  vmbus_msghc_put (struct vmbus_softc*,struct vmbus_msghc*) ; 

__attribute__((used)) static int
vmbus_req_channels(struct vmbus_softc *sc)
{
	struct vmbus_chanmsg_chrequest *req;
	struct vmbus_msghc *mh;
	int error;

	mh = vmbus_msghc_get(sc, sizeof(*req));
	if (mh == NULL)
		return ENXIO;

	req = vmbus_msghc_dataptr(mh);
	req->chm_hdr.chm_type = VMBUS_CHANMSG_TYPE_CHREQUEST;

	error = vmbus_msghc_exec_noresult(mh);
	vmbus_msghc_put(sc, mh);

	return error;
}