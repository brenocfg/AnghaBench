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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct i40e_lldp_org_tlv {size_t* tlvinfo; int /*<<< orphan*/  typelength; int /*<<< orphan*/  ouisubtype; } ;
struct i40e_dcbx_config {scalar_t__ numapps; TYPE_1__* app; } ;
struct TYPE_2__ {int priority; int selector; int protocolid; } ;

/* Variables and functions */
 size_t I40E_DCBX_MAX_APPS ; 
 int /*<<< orphan*/  I40E_HTONL (scalar_t__) ; 
 int /*<<< orphan*/  I40E_HTONS (size_t) ; 
 int I40E_IEEE_8021QAZ_OUI ; 
 size_t I40E_IEEE_APP_PRIO_SHIFT ; 
 int I40E_IEEE_SUBTYPE_APP_PRI ; 
 int I40E_LLDP_TLV_OUI_SHIFT ; 
 size_t I40E_LLDP_TLV_TYPE_SHIFT ; 
 size_t I40E_TLV_TYPE_ORG ; 

__attribute__((used)) static void i40e_add_ieee_app_pri_tlv(struct i40e_lldp_org_tlv *tlv,
				      struct i40e_dcbx_config *dcbcfg)
{
	u16 typelength, length, offset = 0;
	u8 priority, selector, i = 0;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	/* No APP TLVs then just return */
	if (dcbcfg->numapps == 0)
		return;
	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_APP_PRI);
	tlv->ouisubtype = I40E_HTONL(ouisubtype);

	/* Move offset to App Priority Table */
	offset++;
	/* Application Priority Table (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Priority|Rsrvd| Sel |    Protocol ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	while (i < dcbcfg->numapps) {
		priority = dcbcfg->app[i].priority & 0x7;
		selector = dcbcfg->app[i].selector & 0x7;
		buf[offset] = (priority << I40E_IEEE_APP_PRIO_SHIFT) | selector;
		buf[offset + 1] = (dcbcfg->app[i].protocolid >> 0x8) & 0xFF;
		buf[offset + 2] =  dcbcfg->app[i].protocolid & 0xFF;
		/* Move to next app */
		offset += 3;
		i++;
		if (i >= I40E_DCBX_MAX_APPS)
			break;
	}
	/* length includes size of ouisubtype + 1 reserved + 3*numapps */
	length = sizeof(tlv->ouisubtype) + 1 + (i*3);
	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
		(length & 0x1FF));
	tlv->typelength = I40E_HTONS(typelength);
}