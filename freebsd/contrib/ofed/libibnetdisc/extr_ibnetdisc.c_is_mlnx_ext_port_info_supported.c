#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {TYPE_1__* node; } ;
typedef  TYPE_2__ ibnd_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_DEVID_F ; 
 int /*<<< orphan*/  IB_NODE_VENDORID_F ; 
 int /*<<< orphan*/  mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_mlnx_ext_port_info_supported(ibnd_port_t * port)
{
	uint16_t devid = (uint16_t) mad_get_field(port->node->info, 0, IB_NODE_DEVID_F);
	uint32_t vendorid = (uint32_t) mad_get_field(port->node->info, 0, IB_NODE_VENDORID_F);

	if ((devid >= 0xc738 && devid <= 0xc73b) || devid == 0xcb20 || devid == 0xcf08 ||
	    ((vendorid == 0x119f) &&
	     /* Bull SwitchX */
	     (devid == 0x1b02 || devid == 0x1b50 ||
	      /* Bull SwitchIB and SwitchIB2 */
	      devid == 0x1ba0 ||
	      (devid >= 0x1bd0 && devid <= 0x1bd5))))
		return 1;
	if ((devid >= 0x1003 && devid <= 0x1017) ||
	    ((vendorid == 0x119f) &&
	     /* Bull ConnectX3 */
	     (devid == 0x1b33 || devid == 0x1b73 ||
	      devid == 0x1b40 || devid == 0x1b41 ||
	      devid == 0x1b60 || devid == 0x1b61 ||
	     /* Bull ConnectIB */
	      devid == 0x1b83 ||
	      devid == 0x1b93 || devid == 0x1b94 ||
	      /* Bull ConnectX4 */
	      devid == 0x1bb4 || devid == 0x1bb5 ||
	      devid == 0x1bc4)))
		return 1;
	return 0;
}