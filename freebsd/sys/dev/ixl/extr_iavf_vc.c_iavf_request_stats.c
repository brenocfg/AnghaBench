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
typedef  int /*<<< orphan*/  vqs ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_queue_select {int /*<<< orphan*/  vsi_id; } ;
struct iavf_sc {int /*<<< orphan*/  dev; TYPE_1__* vsi_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_GET_STATS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int iavf_send_pf_msg (struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
iavf_request_stats(struct iavf_sc *sc)
{
	struct virtchnl_queue_select vqs;
	int error = 0;

	vqs.vsi_id = sc->vsi_res->vsi_id;
	/* Low priority, we don't need to error check */
	error = iavf_send_pf_msg(sc, VIRTCHNL_OP_GET_STATS,
	    (u8 *)&vqs, sizeof(vqs));
	if (error)
		device_printf(sc->dev, "Error sending stats request to PF: %d\n", error);
	
	return (0);
}