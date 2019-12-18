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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u32 ;
struct virtchnl_rss_hena {int hena; } ;
struct ixl_vf {int /*<<< orphan*/  vf_num; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VFQF_HENA1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTCHNL_OP_SET_RSS_HENA ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_send_vf_ack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_vf_set_rss_hena_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{
	struct i40e_hw *hw;
	struct virtchnl_rss_hena *hena;

	hw = &pf->hw;

	if (msg_size < sizeof(*hena)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_SET_RSS_HENA,
		    I40E_ERR_PARAM);
		return;
	}

	hena = msg;

	/* Set HENA */
	i40e_write_rx_ctl(hw, I40E_VFQF_HENA1(0, vf->vf_num), (u32)hena->hena);
	i40e_write_rx_ctl(hw, I40E_VFQF_HENA1(1, vf->vf_num), (u32)(hena->hena >> 32));

	DDPRINTF(pf->dev, "VF %d: Programmed HENA with 0x%016lx",
	    vf->vf_num, hena->hena);

	ixl_send_vf_ack(pf, vf, VIRTCHNL_OP_SET_RSS_HENA);
}