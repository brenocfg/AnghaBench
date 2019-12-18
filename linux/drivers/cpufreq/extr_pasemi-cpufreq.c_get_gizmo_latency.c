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
typedef  int u32 ;

/* Variables and functions */
 int SDCPWR_GIZTIME_GR ; 
 int SDCPWR_GIZTIME_LONGLOCK ; 
 scalar_t__ SDCPWR_GIZTIME_REG ; 
 int in_le32 (scalar_t__) ; 
 scalar_t__ sdcpwr_mapbase ; 

__attribute__((used)) static int get_gizmo_latency(void)
{
	u32 giztime, ret;

	giztime = in_le32(sdcpwr_mapbase + SDCPWR_GIZTIME_REG);

	/* just provide the upper bound */
	if (giztime & SDCPWR_GIZTIME_GR)
		ret = (giztime & SDCPWR_GIZTIME_LONGLOCK) * 128000;
	else
		ret = (giztime & SDCPWR_GIZTIME_LONGLOCK) * 1000;

	return ret;
}