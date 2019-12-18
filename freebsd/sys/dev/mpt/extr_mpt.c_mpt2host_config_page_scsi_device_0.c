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
typedef  int /*<<< orphan*/  CONFIG_PAGE_SCSI_DEVICE_0 ;

/* Variables and functions */
 int /*<<< orphan*/  Information ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NegotiatedParameters ; 

void
mpt2host_config_page_scsi_device_0(CONFIG_PAGE_SCSI_DEVICE_0 *sd0)
{

	MPT_2_HOST32(sd0, NegotiatedParameters);
	MPT_2_HOST32(sd0, Information);
}