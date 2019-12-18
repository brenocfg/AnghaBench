#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_7__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_6__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_5__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_FC_PORT_0 ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentSpeed ; 
 int /*<<< orphan*/  DiscoveredPortsCount ; 
 TYPE_4__ FabricWWNN ; 
 TYPE_3__ FabricWWPN ; 
 int /*<<< orphan*/  Flags ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxFrameSize ; 
 int /*<<< orphan*/  MaxInitiators ; 
 int /*<<< orphan*/  PortIdentifier ; 
 int /*<<< orphan*/  SupportedServiceClass ; 
 int /*<<< orphan*/  SupportedSpeeds ; 
 TYPE_2__ WWNN ; 
 TYPE_1__ WWPN ; 

void
mpt2host_config_page_fc_port_0(CONFIG_PAGE_FC_PORT_0 *fp0)
{

	MPT_2_HOST32(fp0, Flags);
	MPT_2_HOST32(fp0, PortIdentifier);
	MPT_2_HOST32(fp0, WWNN.Low);
	MPT_2_HOST32(fp0, WWNN.High);
	MPT_2_HOST32(fp0, WWPN.Low);
	MPT_2_HOST32(fp0, WWPN.High);
	MPT_2_HOST32(fp0, SupportedServiceClass);
	MPT_2_HOST32(fp0, SupportedSpeeds);
	MPT_2_HOST32(fp0, CurrentSpeed);
	MPT_2_HOST32(fp0, MaxFrameSize);
	MPT_2_HOST32(fp0, FabricWWNN.Low);
	MPT_2_HOST32(fp0, FabricWWNN.High);
	MPT_2_HOST32(fp0, FabricWWPN.Low);
	MPT_2_HOST32(fp0, FabricWWPN.High);
	MPT_2_HOST32(fp0, DiscoveredPortsCount);
	MPT_2_HOST32(fp0, MaxInitiators);
}