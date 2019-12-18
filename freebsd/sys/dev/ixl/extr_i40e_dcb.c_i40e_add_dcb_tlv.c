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
typedef  int u16 ;
struct i40e_lldp_org_tlv {int dummy; } ;
struct i40e_dcbx_config {int dummy; } ;

/* Variables and functions */
#define  I40E_IEEE_TLV_ID_APP_PRI 131 
#define  I40E_IEEE_TLV_ID_ETS_CFG 130 
#define  I40E_IEEE_TLV_ID_ETS_REC 129 
#define  I40E_IEEE_TLV_ID_PFC_CFG 128 
 int /*<<< orphan*/  i40e_add_ieee_app_pri_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_add_ieee_ets_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_add_ieee_etsrec_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 
 int /*<<< orphan*/  i40e_add_ieee_pfc_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*) ; 

__attribute__((used)) static void i40e_add_dcb_tlv(struct i40e_lldp_org_tlv *tlv,
			     struct i40e_dcbx_config *dcbcfg,
			     u16 tlvid)
{
	switch (tlvid) {
	case I40E_IEEE_TLV_ID_ETS_CFG:
		i40e_add_ieee_ets_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_TLV_ID_ETS_REC:
		i40e_add_ieee_etsrec_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_TLV_ID_PFC_CFG:
		i40e_add_ieee_pfc_tlv(tlv, dcbcfg);
		break;
	case I40E_IEEE_TLV_ID_APP_PRI:
		i40e_add_ieee_app_pri_tlv(tlv, dcbcfg);
		break;
	default:
		break;
	}
}