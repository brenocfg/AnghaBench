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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct i40e_lldp_org_tlv {int /*<<< orphan*/  typelength; } ;
struct i40e_dcbx_config {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 scalar_t__ I40E_LLDPDU_SIZE ; 
 scalar_t__ I40E_LLDP_TLV_LEN_MASK ; 
 scalar_t__ I40E_LLDP_TLV_LEN_SHIFT ; 
 scalar_t__ I40E_NTOHS (int /*<<< orphan*/ ) ; 
 int I40E_SUCCESS ; 
 scalar_t__ I40E_TLV_ID_END_OF_LLDPPDU ; 
 scalar_t__ I40E_TLV_ID_START ; 
 int /*<<< orphan*/  i40e_add_dcb_tlv (struct i40e_lldp_org_tlv*,struct i40e_dcbx_config*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_dcb_config_to_lldp(u8 *lldpmib, u16 *miblen,
					      struct i40e_dcbx_config *dcbcfg)
{
	u16 length, offset = 0, tlvid = I40E_TLV_ID_START;
	enum i40e_status_code ret = I40E_SUCCESS;
	struct i40e_lldp_org_tlv *tlv;
	u16 typelength;

	tlv = (struct i40e_lldp_org_tlv *)lldpmib;
	while (1) {
		i40e_add_dcb_tlv(tlv, dcbcfg, tlvid++);
		typelength = I40E_NTOHS(tlv->typelength);
		length = (u16)((typelength & I40E_LLDP_TLV_LEN_MASK) >>
				I40E_LLDP_TLV_LEN_SHIFT);
		if (length)
			offset += length + 2;
		/* END TLV or beyond LLDPDU size */
		if ((tlvid >= I40E_TLV_ID_END_OF_LLDPPDU) ||
		    (offset > I40E_LLDPDU_SIZE))
			break;
		/* Move to next TLV */
		if (length)
			tlv = (struct i40e_lldp_org_tlv *)((char *)tlv +
			      sizeof(tlv->typelength) + length);
	}
	*miblen = offset;
	return ret;
}