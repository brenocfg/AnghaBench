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
typedef  int u16 ;
struct i40e_lldp_org_tlv {int* tlvinfo; int /*<<< orphan*/  ouisubtype; int /*<<< orphan*/  typelength; } ;
struct i40e_dcb_ets_config {int* prioritytable; int* tcbwtable; int* tsatable; } ;
struct i40e_dcbx_config {struct i40e_dcb_ets_config etsrec; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_HTONL (scalar_t__) ; 
 int /*<<< orphan*/  I40E_HTONS (int) ; 
 int I40E_IEEE_8021QAZ_OUI ; 
 int I40E_IEEE_ETS_PRIO_1_SHIFT ; 
 int I40E_IEEE_ETS_TLV_LENGTH ; 
 int I40E_IEEE_SUBTYPE_ETS_REC ; 
 int I40E_LLDP_TLV_OUI_SHIFT ; 
 int I40E_LLDP_TLV_TYPE_SHIFT ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int I40E_TLV_TYPE_ORG ; 

__attribute__((used)) static void i40e_add_ieee_etsrec_tlv(struct i40e_lldp_org_tlv *tlv,
				     struct i40e_dcbx_config *dcbcfg)
{
	struct i40e_dcb_ets_config *etsrec;
	u16 offset = 0, typelength, i;
	u8 priority0, priority1;
	u8 *buf = tlv->tlvinfo;
	u32 ouisubtype;

	typelength = (u16)((I40E_TLV_TYPE_ORG << I40E_LLDP_TLV_TYPE_SHIFT) |
			I40E_IEEE_ETS_TLV_LENGTH);
	tlv->typelength = I40E_HTONS(typelength);

	ouisubtype = (u32)((I40E_IEEE_8021QAZ_OUI << I40E_LLDP_TLV_OUI_SHIFT) |
			I40E_IEEE_SUBTYPE_ETS_REC);
	tlv->ouisubtype = I40E_HTONL(ouisubtype);

	etsrec = &dcbcfg->etsrec;
	/* First Octet is reserved */
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
		priority0 = etsrec->prioritytable[i * 2] & 0xF;
		priority1 = etsrec->prioritytable[i * 2 + 1] & 0xF;
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
		buf[offset++] = etsrec->tcbwtable[i];

	/* TSA Assignment Table (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		buf[offset++] = etsrec->tsatable[i];
}