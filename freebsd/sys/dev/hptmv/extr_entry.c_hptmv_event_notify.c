#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * sataEvents; int /*<<< orphan*/  event_timer_connect; } ;
struct TYPE_7__ {int adapterId; TYPE_2__* IALData; } ;
typedef  size_t MV_U8 ;
typedef  size_t MV_U32 ;
typedef  TYPE_1__ MV_SATA_ADAPTER ;
typedef  int MV_EVENT_TYPE ;
typedef  int /*<<< orphan*/  MV_BOOLEAN ;
typedef  TYPE_2__ IAL_ADAPTER_T ;

/* Variables and functions */
 size_t EVENT_CONNECT ; 
 size_t EVENT_DISCONNECT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  MV_ERROR (char*,size_t,int) ; 
#define  MV_EVENT_TYPE_ADAPTER_ERROR 129 
#define  MV_EVENT_TYPE_SATA_CABLE 128 
 int /*<<< orphan*/  MV_FALSE ; 
 int /*<<< orphan*/  MV_TRUE ; 
 int /*<<< orphan*/  SATA_EVENT_CHANNEL_CONNECTED ; 
 int /*<<< orphan*/  SATA_EVENT_CHANNEL_DISCONNECTED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  device_change (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hptmv_handle_event_connect ; 
 int /*<<< orphan*/  hptmv_handle_event_disconnect (TYPE_2__*) ; 
 int hz ; 

__attribute__((used)) static MV_BOOLEAN
hptmv_event_notify(MV_SATA_ADAPTER *pMvSataAdapter, MV_EVENT_TYPE eventType,
								   MV_U32 param1, MV_U32 param2)
{
	IAL_ADAPTER_T   *pAdapter = pMvSataAdapter->IALData;

	switch (eventType)
	{
		case MV_EVENT_TYPE_SATA_CABLE:
			{
				MV_U8   channel = param2;

				if (param1 == EVENT_CONNECT)
				{
					pAdapter->sataEvents[channel] = SATA_EVENT_CHANNEL_CONNECTED;
					KdPrint(("RR18xx [%d,%d]: device connected event received\n",
							 pMvSataAdapter->adapterId, channel));
					/* Delete previous timers (if multiple drives connected in the same time */
					callout_reset(&pAdapter->event_timer_connect, 10 * hz, hptmv_handle_event_connect, pAdapter);
				}
				else if (param1 == EVENT_DISCONNECT)
				{
					pAdapter->sataEvents[channel] = SATA_EVENT_CHANNEL_DISCONNECTED;
					KdPrint(("RR18xx [%d,%d]: device disconnected event received \n",
							 pMvSataAdapter->adapterId, channel));
					device_change(pAdapter, channel, FALSE);
					/* Delete previous timers (if multiple drives disconnected in the same time */
					/*callout_reset(&pAdapter->event_timer_disconnect, 10 * hz, hptmv_handle_event_disconnect, pAdapter); */
					/*It is not necessary to wait, handle it directly*/
					hptmv_handle_event_disconnect(pAdapter);
				}
				else
				{

					MV_ERROR("RR18xx: illegal value for param1(%d) at "
							 "connect/disconnect event, host=%d\n", param1,
							 pMvSataAdapter->adapterId );

				}
			}
			break;
		case MV_EVENT_TYPE_ADAPTER_ERROR:
			KdPrint(("RR18xx: DEVICE error event received, pci cause "
					  "reg=%x,  don't how to handle this\n", param1));
			return MV_TRUE;
		default:
			MV_ERROR("RR18xx[%d]: unknown event type (%d)\n",
					 pMvSataAdapter->adapterId, eventType);
			return MV_FALSE;
	}
	return MV_TRUE;
}