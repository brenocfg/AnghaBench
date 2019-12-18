#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct ixl_vsi {int /*<<< orphan*/  vsi_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_2__ aq; TYPE_1__ mac; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct ixl_vsi vsi; struct i40e_hw hw; } ;
struct i40e_aqc_get_set_rss_key_data {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ I40E_MAC_X722 ; 
 int /*<<< orphan*/  I40E_PFQF_HKEY (int) ; 
 int IXL_RSS_KEY_SIZE_REG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct i40e_aqc_get_set_rss_key_data*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_aq_set_rss_key (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_aqc_get_set_rss_key_data*) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_get_default_rss_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ *) ; 

void
ixl_set_rss_key(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	struct ixl_vsi *vsi = &pf->vsi;
	device_t	dev = pf->dev;
	u32 rss_seed[IXL_RSS_KEY_SIZE_REG];
	enum i40e_status_code status;

#ifdef RSS
        /* Fetch the configured RSS key */
        rss_getkey((uint8_t *) &rss_seed);
#else
	ixl_get_default_rss_key(rss_seed);
#endif
	/* Fill out hash function seed */
	if (hw->mac.type == I40E_MAC_X722) {
		struct i40e_aqc_get_set_rss_key_data key_data;
		bcopy(rss_seed, &key_data, 52);
		status = i40e_aq_set_rss_key(hw, vsi->vsi_num, &key_data);
		if (status)
			device_printf(dev,
			    "i40e_aq_set_rss_key status %s, error %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
	} else {
		for (int i = 0; i < IXL_RSS_KEY_SIZE_REG; i++)
			i40e_write_rx_ctl(hw, I40E_PFQF_HKEY(i), rss_seed[i]);
	}
}