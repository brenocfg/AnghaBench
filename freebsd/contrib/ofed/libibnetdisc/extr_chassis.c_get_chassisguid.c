#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_SYSTEM_GUID_F ; 
 int /*<<< orphan*/  IB_NODE_VENDORID_F ; 
 scalar_t__ SS_VENDOR_ID ; 
 scalar_t__ TS_VENDOR_ID ; 
 scalar_t__ XS_VENDOR_ID ; 
 scalar_t__ ibnd_is_xsigo_guid (int /*<<< orphan*/ ) ; 
 scalar_t__ mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_get_field64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topspin_chassisguid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsigo_chassisguid (TYPE_1__*) ; 

__attribute__((used)) static uint64_t get_chassisguid(ibnd_node_t * node)
{
	uint32_t vendid = mad_get_field(node->info, 0, IB_NODE_VENDORID_F);
	uint64_t sysimgguid =
	    mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F);

	if (vendid == TS_VENDOR_ID || vendid == SS_VENDOR_ID)
		return topspin_chassisguid(sysimgguid);
	else if (vendid == XS_VENDOR_ID || ibnd_is_xsigo_guid(sysimgguid))
		return xsigo_chassisguid(node);
	else
		return sysimgguid;
}