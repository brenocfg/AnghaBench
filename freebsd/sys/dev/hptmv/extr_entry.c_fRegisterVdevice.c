#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** pVDevice; } ;
struct TYPE_10__ {TYPE_2__ VBus; TYPE_1__* VDevices; } ;
struct TYPE_8__ {scalar_t__ vf_online; scalar_t__ VDeviceType; scalar_t__ vf_bootmark; TYPE_2__* pVBus; struct TYPE_8__* pParent; } ;
typedef  TYPE_1__* PVDevice ;
typedef  TYPE_2__* PVBus ;
typedef  TYPE_3__ IAL_ADAPTER_T ;

/* Variables and functions */
 int MAX_VDEVICE_PER_VBUS ; 
 int MV_SATA_CHANNELS_NUM ; 
 scalar_t__ VD_SPARE ; 
 TYPE_1__* fGetFirstChild (TYPE_1__*) ; 
 int /*<<< orphan*/  fResetBootMark (TYPE_1__*) ; 

__attribute__((used)) static void
fRegisterVdevice(IAL_ADAPTER_T *pAdapter)
{
	PVDevice pPhysical, pLogical;
	PVBus  pVBus;
	int i,j;

	for(i=0;i<MV_SATA_CHANNELS_NUM;i++) {
		pPhysical = &(pAdapter->VDevices[i]);
		pLogical = pPhysical;
		while (pLogical->pParent) pLogical = pLogical->pParent;
		if (pLogical->vf_online==0) {
			pPhysical->vf_bootmark = pLogical->vf_bootmark = 0;
			continue;
		}
		if (pLogical->VDeviceType==VD_SPARE || pPhysical!=fGetFirstChild(pLogical)) 
			continue;

		pVBus = &pAdapter->VBus;
		if(pVBus)
		{
			j=0;
			while(j<MAX_VDEVICE_PER_VBUS && pVBus->pVDevice[j]) j++;
			if(j<MAX_VDEVICE_PER_VBUS){
				pVBus->pVDevice[j] = pLogical; 
				pLogical->pVBus = pVBus;

				if (j>0 && pLogical->vf_bootmark) {
					if (pVBus->pVDevice[0]->vf_bootmark) {
						fResetBootMark(pLogical);
					}
					else {
						do { pVBus->pVDevice[j] = pVBus->pVDevice[j-1]; } while (--j);
						pVBus->pVDevice[0] = pLogical;
					}
				}
			}
		}
	}
}