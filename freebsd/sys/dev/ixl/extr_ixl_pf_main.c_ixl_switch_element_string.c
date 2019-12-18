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
struct sbuf {int dummy; } ;
struct i40e_aqc_switch_config_element_resp {int element_type; int /*<<< orphan*/  element_info; } ;

/* Variables and functions */
#define  I40E_AQ_SW_ELEM_TYPE_BMC 136 
#define  I40E_AQ_SW_ELEM_TYPE_EMP 135 
#define  I40E_AQ_SW_ELEM_TYPE_MAC 134 
#define  I40E_AQ_SW_ELEM_TYPE_PA 133 
#define  I40E_AQ_SW_ELEM_TYPE_PF 132 
#define  I40E_AQ_SW_ELEM_TYPE_PV 131 
#define  I40E_AQ_SW_ELEM_TYPE_VEB 130 
#define  I40E_AQ_SW_ELEM_TYPE_VF 129 
#define  I40E_AQ_SW_ELEM_TYPE_VSI 128 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 

char *
ixl_switch_element_string(struct sbuf *s,
    struct i40e_aqc_switch_config_element_resp *element)
{
	sbuf_clear(s);

	switch (element->element_type) {
	case I40E_AQ_SW_ELEM_TYPE_MAC:
		sbuf_printf(s, "MAC %3d", element->element_info);
		break;
	case I40E_AQ_SW_ELEM_TYPE_PF:
		sbuf_printf(s, "PF  %3d", element->element_info);
		break;
	case I40E_AQ_SW_ELEM_TYPE_VF:
		sbuf_printf(s, "VF  %3d", element->element_info);
		break;
	case I40E_AQ_SW_ELEM_TYPE_EMP:
		sbuf_cat(s, "EMP");
		break;
	case I40E_AQ_SW_ELEM_TYPE_BMC:
		sbuf_cat(s, "BMC");
		break;
	case I40E_AQ_SW_ELEM_TYPE_PV:
		sbuf_cat(s, "PV");
		break;
	case I40E_AQ_SW_ELEM_TYPE_VEB:
		sbuf_cat(s, "VEB");
		break;
	case I40E_AQ_SW_ELEM_TYPE_PA:
		sbuf_cat(s, "PA");
		break;
	case I40E_AQ_SW_ELEM_TYPE_VSI:
		sbuf_printf(s, "VSI %3d", element->element_info);
		break;
	default:
		sbuf_cat(s, "?");
		break;
	}

	sbuf_finish(s);
	return sbuf_data(s);
}