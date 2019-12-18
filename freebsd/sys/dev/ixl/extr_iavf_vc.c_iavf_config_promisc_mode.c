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
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_promisc_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  vsi_id; } ;
struct iavf_sc {int /*<<< orphan*/  promisc_flags; TYPE_1__* vsi_res; } ;
typedef  int /*<<< orphan*/  pinfo ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
iavf_config_promisc_mode(struct iavf_sc *sc)
{
	struct virtchnl_promisc_info pinfo;

	pinfo.vsi_id = sc->vsi_res->vsi_id;
	pinfo.flags = sc->promisc_flags;

	iavf_send_pf_msg(sc, VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
	    (u8 *)&pinfo, sizeof(pinfo));
	return (0);
}