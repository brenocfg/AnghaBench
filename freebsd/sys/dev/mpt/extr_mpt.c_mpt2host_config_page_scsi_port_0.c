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
typedef  int /*<<< orphan*/  CONFIG_PAGE_SCSI_PORT_0 ;

/* Variables and functions */
 int /*<<< orphan*/  Capabilities ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PhysicalInterface ; 

void
mpt2host_config_page_scsi_port_0(CONFIG_PAGE_SCSI_PORT_0 *sp0)
{

	MPT_2_HOST32(sp0, Capabilities);
	MPT_2_HOST32(sp0, PhysicalInterface);
}