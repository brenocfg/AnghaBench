#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {int /*<<< orphan*/  media; TYPE_1__* shared; int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  phy_types; } ;
struct TYPE_5__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_3__ phy; TYPE_2__ aq; } ;
struct ixl_pf {int /*<<< orphan*/  supported_speeds; struct i40e_hw hw; struct ixl_vsi vsi; } ;
struct ifnet {scalar_t__ if_mtu; } ;
struct i40e_aq_get_phy_abilities_resp {int /*<<< orphan*/  link_speed; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ isc_max_frame_size; } ;

/* Variables and functions */
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int I40E_ERR_UNKNOWN_PHY ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int i40e_aq_get_phy_capabilities (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40e_aq_get_phy_abilities_resp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 
 int /*<<< orphan*/  if_initbaudrate (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixl_add_ifmedia (struct ixl_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_max_aq_speed_to_value (int /*<<< orphan*/ ) ; 

int
ixl_setup_interface(device_t dev, struct ixl_pf *pf)
{
	struct ixl_vsi *vsi = &pf->vsi;
	if_ctx_t ctx = vsi->ctx;
	struct i40e_hw *hw = &pf->hw;
	struct ifnet *ifp = iflib_get_ifp(ctx);
	struct i40e_aq_get_phy_abilities_resp abilities;
	enum i40e_status_code aq_error = 0;

	INIT_DBG_DEV(dev, "begin");

	vsi->shared->isc_max_frame_size =
	    ifp->if_mtu + ETHER_HDR_LEN + ETHER_CRC_LEN
	    + ETHER_VLAN_ENCAP_LEN;

	aq_error = i40e_aq_get_phy_capabilities(hw,
	    FALSE, TRUE, &abilities, NULL);
	/* May need delay to detect fiber correctly */
	if (aq_error == I40E_ERR_UNKNOWN_PHY) {
		/* TODO: Maybe just retry this in a task... */
		i40e_msec_delay(200);
		aq_error = i40e_aq_get_phy_capabilities(hw, FALSE,
		    TRUE, &abilities, NULL);
	}
	if (aq_error) {
		if (aq_error == I40E_ERR_UNKNOWN_PHY)
			device_printf(dev, "Unknown PHY type detected!\n");
		else
			device_printf(dev,
			    "Error getting supported media types, err %d,"
			    " AQ error %d\n", aq_error, hw->aq.asq_last_status);
	} else {
		pf->supported_speeds = abilities.link_speed;
#if __FreeBSD_version >= 1100000
		if_setbaudrate(ifp, ixl_max_aq_speed_to_value(pf->supported_speeds));
#else
		if_initbaudrate(ifp, ixl_max_aq_speed_to_value(pf->supported_speeds));
#endif

		ixl_add_ifmedia(vsi, hw->phy.phy_types);
	}

	/* Use autoselect media by default */
	ifmedia_add(vsi->media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(vsi->media, IFM_ETHER | IFM_AUTO);

	return (0);
}