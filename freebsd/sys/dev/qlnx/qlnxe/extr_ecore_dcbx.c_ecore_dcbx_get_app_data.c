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
typedef  void* u32 ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dcbx_params {int num_app_entries; void* app_error; void* app_valid; void* app_willing; struct ecore_app_entry* app_entry; } ;
struct ecore_app_entry {int ethtype; int /*<<< orphan*/  proto_type; void* proto_id; int /*<<< orphan*/  prio; void* sf_ieee; } ;
struct dcbx_app_priority_feature {int /*<<< orphan*/  flags; } ;
struct dcbx_app_priority_entry {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_ENABLED ; 
 int /*<<< orphan*/  DCBX_APP_ERROR ; 
 int /*<<< orphan*/  DCBX_APP_NUM_ENTRIES ; 
 int /*<<< orphan*/  DCBX_APP_PRI_MAP ; 
 int /*<<< orphan*/  DCBX_APP_PROTOCOL_ID ; 
 int /*<<< orphan*/  DCBX_APP_SF ; 
 int /*<<< orphan*/  DCBX_APP_SF_IEEE ; 
#define  DCBX_APP_SF_IEEE_ETHTYPE 132 
#define  DCBX_APP_SF_IEEE_RESERVED 131 
#define  DCBX_APP_SF_IEEE_TCP_PORT 130 
#define  DCBX_APP_SF_IEEE_TCP_UDP_PORT 129 
#define  DCBX_APP_SF_IEEE_UDP_PORT 128 
 int /*<<< orphan*/  DCBX_APP_WILLING ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 void* ECORE_DCBX_SF_IEEE_ETHTYPE ; 
 void* ECORE_DCBX_SF_IEEE_TCP_PORT ; 
 void* ECORE_DCBX_SF_IEEE_TCP_UDP_PORT ; 
 void* ECORE_DCBX_SF_IEEE_UDP_PORT ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 
 void* GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_dcbx_get_app_priority (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_dcbx_get_app_protocol_type (struct ecore_hwfn*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ecore_dcbx_get_app_data(struct ecore_hwfn *p_hwfn,
			struct dcbx_app_priority_feature *p_app,
			struct dcbx_app_priority_entry *p_tbl,
			struct ecore_dcbx_params *p_params, bool ieee)
{
	struct ecore_app_entry *entry;
	u8 pri_map;
	int i;

	p_params->app_willing = GET_MFW_FIELD(p_app->flags, DCBX_APP_WILLING);
	p_params->app_valid = GET_MFW_FIELD(p_app->flags, DCBX_APP_ENABLED);
	p_params->app_error = GET_MFW_FIELD(p_app->flags, DCBX_APP_ERROR);
	p_params->num_app_entries = GET_MFW_FIELD(p_app->flags,
						  DCBX_APP_NUM_ENTRIES);
	for (i = 0; i < p_params->num_app_entries; i++) {
		entry = &p_params->app_entry[i];
		if (ieee) {
			u8 sf_ieee;
			u32 val;

			sf_ieee = GET_MFW_FIELD(p_tbl[i].entry,
						DCBX_APP_SF_IEEE);
			switch (sf_ieee) {
			case DCBX_APP_SF_IEEE_RESERVED:
				/* Old MFW */
				val = GET_MFW_FIELD(p_tbl[i].entry,
						    DCBX_APP_SF);
				entry->sf_ieee = val ?
					ECORE_DCBX_SF_IEEE_TCP_UDP_PORT :
					ECORE_DCBX_SF_IEEE_ETHTYPE;
				break;
			case DCBX_APP_SF_IEEE_ETHTYPE:
				entry->sf_ieee = ECORE_DCBX_SF_IEEE_ETHTYPE;
				break;
			case DCBX_APP_SF_IEEE_TCP_PORT:
				entry->sf_ieee = ECORE_DCBX_SF_IEEE_TCP_PORT;
				break;
			case DCBX_APP_SF_IEEE_UDP_PORT:
				entry->sf_ieee = ECORE_DCBX_SF_IEEE_UDP_PORT;
				break;
			case DCBX_APP_SF_IEEE_TCP_UDP_PORT:
				entry->sf_ieee = ECORE_DCBX_SF_IEEE_TCP_UDP_PORT;
				break;
			}
		} else {
			entry->ethtype = !(GET_MFW_FIELD(p_tbl[i].entry,
							 DCBX_APP_SF));
		}

		pri_map = GET_MFW_FIELD(p_tbl[i].entry, DCBX_APP_PRI_MAP);
		ecore_dcbx_get_app_priority(pri_map, &entry->prio);
		entry->proto_id = GET_MFW_FIELD(p_tbl[i].entry,
						DCBX_APP_PROTOCOL_ID);
		ecore_dcbx_get_app_protocol_type(p_hwfn, p_tbl[i].entry,
						 entry->proto_id,
						 &entry->proto_type, ieee);
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_DCB,
		   "APP params: willing %d, valid %d error = %d\n",
		   p_params->app_willing, p_params->app_valid,
		   p_params->app_error);
}