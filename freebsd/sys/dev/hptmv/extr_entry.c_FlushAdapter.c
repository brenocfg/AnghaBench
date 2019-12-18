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
struct TYPE_4__ {scalar_t__* pVDevice; } ;
struct TYPE_5__ {TYPE_1__ VBus; } ;
typedef  scalar_t__ PVDevice ;
typedef  TYPE_2__ IAL_ADAPTER_T ;

/* Variables and functions */
 int MAX_VDEVICE_PER_VBUS ; 
 int /*<<< orphan*/  fFlushVDev (scalar_t__) ; 
 int /*<<< orphan*/  hpt_printk (char*) ; 

__attribute__((used)) static void
FlushAdapter(IAL_ADAPTER_T *pAdapter)
{
	int i;

	hpt_printk(("flush all devices\n"));
	
	/* flush all devices */
	for (i=0; i<MAX_VDEVICE_PER_VBUS; i++) {
		PVDevice pVDev = pAdapter->VBus.pVDevice[i];
		if(pVDev) fFlushVDev(pVDev);
	}
}