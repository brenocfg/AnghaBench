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
struct ifnet {int dummy; } ;
struct TYPE_2__ {struct ifnet* ifp; } ;
struct iavf_sc {int /*<<< orphan*/  queues_enabled; TYPE_1__ vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_DISABLE_QUEUES ; 
 scalar_t__ atomic_load_acq_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_disable_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  iavf_send_vc_msg_sleep (struct iavf_sc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_stop(struct iavf_sc *sc)
{
	struct ifnet *ifp;

	ifp = sc->vsi.ifp;

	iavf_disable_intr(&sc->vsi);

	if (atomic_load_acq_32(&sc->queues_enabled))
		iavf_send_vc_msg_sleep(sc, IAVF_FLAG_AQ_DISABLE_QUEUES);
}