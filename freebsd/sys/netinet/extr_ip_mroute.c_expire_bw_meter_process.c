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
struct vnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW_METER_PERIOD ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (struct vnet*) ; 
 int MRT_MFC_BW_UPCALL ; 
 int /*<<< orphan*/  V_bw_meter_ch ; 
 int V_mrt_api_config ; 
 int /*<<< orphan*/  bw_meter_process () ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 

__attribute__((used)) static void
expire_bw_meter_process(void *arg)
{
    CURVNET_SET((struct vnet *) arg);

    if (V_mrt_api_config & MRT_MFC_BW_UPCALL)
	bw_meter_process();

    callout_reset(&V_bw_meter_ch, BW_METER_PERIOD, expire_bw_meter_process,
	curvnet);
    CURVNET_RESTORE();
}