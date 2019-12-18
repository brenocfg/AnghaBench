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
struct iavf_sc {int /*<<< orphan*/  dev; TYPE_1__* vf_res; } ;
struct TYPE_2__ {int vf_cap_flags; } ;

/* Variables and functions */
 int VIRTCHNL_VF_OFFLOAD_RSS_PF ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_REG ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iavf_config_rss_pf (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_config_rss_reg (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_dbg_info (struct iavf_sc*,char*) ; 

__attribute__((used)) static void
iavf_config_rss(struct iavf_sc *sc)
{
	if (sc->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_RSS_REG) {
		iavf_dbg_info(sc, "Setting up RSS using VF registers...");
		iavf_config_rss_reg(sc);
	} else if (sc->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_RSS_PF) {
		iavf_dbg_info(sc, "Setting up RSS using messages to PF...");
		iavf_config_rss_pf(sc);
	} else
		device_printf(sc->dev, "VF does not support RSS capability sent by PF.\n");
}