#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ pcap_if_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  size_t ULONG ;
struct TYPE_7__ {TYPE_1__* beginning; } ;
struct TYPE_6__ {scalar_t__ (* QueryPortList ) (int /*<<< orphan*/ **,size_t*) ;scalar_t__ (* FreePortList ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ TC_STATUS ;
typedef  scalar_t__ TC_API_LOAD_STATUS ;
typedef  int /*<<< orphan*/ * PTC_PORT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ LoadTcFunctions () ; 
 scalar_t__ TC_API_LOADED ; 
 scalar_t__ TC_SUCCESS ; 
 TYPE_1__* TcCreatePcapIfFromPort (int /*<<< orphan*/ ) ; 
 TYPE_3__* devlistp ; 
 TYPE_2__ g_TcFunctions ; 
 scalar_t__ stub1 (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

int
TcFindAllDevs(pcap_if_list_t *devlist, char *errbuf)
{
	TC_API_LOAD_STATUS loadStatus;
	ULONG numPorts;
	PTC_PORT pPorts = NULL;
	TC_STATUS status;
	int result = 0;
	pcap_if_t *dev, *cursor;
	ULONG i;

	do
	{
		loadStatus = LoadTcFunctions();

		if (loadStatus != TC_API_LOADED)
		{
			result = 0;
			break;
		}

		/*
		 * enumerate the ports, and add them to the list
		 */
		status = g_TcFunctions.QueryPortList(&pPorts, &numPorts);

		if (status != TC_SUCCESS)
		{
			result = 0;
			break;
		}

		for (i = 0; i < numPorts; i++)
		{
			/*
			 * transform the port into an entry in the list
			 */
			dev = TcCreatePcapIfFromPort(pPorts[i]);

			if (dev != NULL)
			{
				/*
				 * append it at the end
				 */
				if (devlistp->beginning == NULL)
				{
					devlistp->beginning = dev;
				}
				else
				{
					for (cursor = devlistp->beginning;
					    cursor->next != NULL;
					    cursor = cursor->next);
					cursor->next = dev;
				}
			}
		}

		if (numPorts > 0)
		{
			/*
			 * ignore the result here
			 */
			status = g_TcFunctions.FreePortList(pPorts);
		}

	}while(FALSE);

	return result;
}