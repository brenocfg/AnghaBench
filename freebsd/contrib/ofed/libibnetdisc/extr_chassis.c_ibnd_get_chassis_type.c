#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t ch_type; char* ch_type_str; int /*<<< orphan*/  info; int /*<<< orphan*/  chassis; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 char** ChassisTypeStr ; 
 int /*<<< orphan*/  IBND_DEBUG (char*) ; 
 int /*<<< orphan*/  IB_NODE_VENDORID_F ; 
 size_t ISR4200_CT ; 
#define  MLX_VENDOR_ID 129 
 size_t UNRESOLVED_CT ; 
#define  VTR_VENDOR_ID 128 
 int mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *ibnd_get_chassis_type(ibnd_node_t * node)
{
	int chassis_type;

	if (!node) {
		IBND_DEBUG("node parameter NULL\n");
		return NULL;
	}

	if (!node->chassis)
		return NULL;

	chassis_type = mad_get_field(node->info, 0, IB_NODE_VENDORID_F);

	switch (chassis_type)
	{
		case VTR_VENDOR_ID: /* Voltaire chassis */
		{
			if (node->ch_type == UNRESOLVED_CT || node->ch_type > ISR4200_CT)
				return NULL;
			return ChassisTypeStr[node->ch_type];
		}
		case MLX_VENDOR_ID:
		{
			if (node->ch_type_str[0] == '\0')
				return NULL;
			return node->ch_type_str;
		}
		default:
		{
			break;
		}
	}
	return NULL;
}