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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct i40e_lldp_org_tlv {int* tlvinfo; int /*<<< orphan*/  ouisubtype; int /*<<< orphan*/  typelength; } ;
struct i40e_dcb_ets_config {int maxtcs; int* prioritytable; int* tcbwtable; int* tsatable; scalar_t__ willing; } ;
struct i40e_dcbx_config {struct i40e_dcb_ets_config etscfg; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_HTONL (scalar_t__) ; 
 int /*<<< orphan*/  I40E_HTONS (size_t) ; 
 int I40E_IEEE_8021QAZ_OUI ; 
 int I40E_IEEE_ETS_MAXTC_MASK ; 
 int I40E_IEEE_ETS_PRIO_1_SHIFT ; 
 int I40E_IEEE_ETS_TLV_LENGTH ; 
 int /*<<< orphan*/  I40E_IEEE_ETS_WILLING_SHIFT ; 
 int I40E_IEEE_SUBTYPE_ETS_CFG ; 
 int I40E_LLDP_TLV_OUI_SHIFT ; 
 int I40E_LLDP_TLV_TYPE_SHIFT ; 
 size_t I40E_MAX_TRAFFIC_CLASS ; 
 int I40E_TLV_TYPE_ORG ; 

__attribute__((used)) static void i40e_add_ieee_ets_tlv(struct i40e_lldp_org_tlv *tlv,
				  struct i40e_dcbx_config *dcbcfg)
{
	u8 priority0, priority1, maxtcwilling = 0;
	struct i40e_dcb_ets_config *etscfg;
	u16 offset = 0, typelength, i;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
			I40E_IEEE_ETS_TLV_LENGTH);
	tlv->typelength = I40E_HTONS(typelength);

	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_ETS_CFG);
	tlv->ouisubtype = I40E_HTONL(ouisubtype);

	/* First Octet post subtype
	 * --------------------------
	 * |will-|CBS  | Re-  | Max |
	 * |ing  |     |served| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	if (etscfg->willing)
		maxtcwilling = BIT(I40E_IEEE_ETS_WILLING_SHIFT);
	maxtcwilling |= etscfg->maxtcs & I40E_IEEE_ETS_MAXTC_MASK;
	buf[offset] = maxtcwilling;

	/* Move offset to Priority Assignment Table */
	offset++;

	/* Priority Assignment Table (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pri0|pri1|pri2|pri3|pri4|pri5|pri6|pri7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	for (i = 0; i < 4; i++) {
		priority0 = etscfg->prioritytable[i * 2] & 0xF;
		priority1 = etscfg->prioritytable[i * 2 + 1] & 0xF;
		buf[offset] = (priority0 << I40E_IEEE_ETS_PRIO_1_SHIFT) |
				priority1;
		offset++;
	}

	/* TC Bandwidth Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etscfg->tcbwtable[i];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etscfg->tsatable[i];
}