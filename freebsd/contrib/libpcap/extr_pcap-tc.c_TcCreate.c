#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcap_tc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;
typedef  size_t ULONG ;
struct TYPE_6__ {scalar_t__ (* QueryPortList ) (int /*<<< orphan*/ **,size_t*) ;int /*<<< orphan*/  (* FreePortList ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* PortGetName ) (int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ TC_STATUS ;
typedef  int /*<<< orphan*/ * PTC_PORT ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ LoadTcFunctions () ; 
 scalar_t__ TC_API_LOADED ; 
 scalar_t__ TC_SUCCESS ; 
 int TRUE ; 
 int /*<<< orphan*/  TcActivate ; 
 int /*<<< orphan*/  TcGetNonBlock ; 
 int /*<<< orphan*/  TcSetNonBlock ; 
 TYPE_3__ g_TcFunctions ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

pcap_t *
TcCreate(const char *device, char *ebuf, int *is_ours)
{
	ULONG numPorts;
	PTC_PORT pPorts = NULL;
	TC_STATUS status;
	int is_tc;
	ULONG i;
	pcap_t *p;

	if (LoadTcFunctions() != TC_API_LOADED)
	{
		/*
		 * XXX - report this as an error rather than as
		 * "not a TurboCap device"?
		 */
		*is_ours = 0;
		return NULL;
	}

	/*
	 * enumerate the ports, and add them to the list
	 */
	status = g_TcFunctions.QueryPortList(&pPorts, &numPorts);

	if (status != TC_SUCCESS)
	{
		/*
		 * XXX - report this as an error rather than as
		 * "not a TurboCap device"?
		 */
		*is_ours = 0;
		return NULL;
	}

	is_tc = FALSE;
	for (i = 0; i < numPorts; i++)
	{
		if (strcmp(g_TcFunctions.PortGetName(pPorts[i]), device) == 0)
		{
			is_tc = TRUE;
			break;
		}
	}

	if (numPorts > 0)
	{
		/*
		 * ignore the result here
		 */
		(void)g_TcFunctions.FreePortList(pPorts);
	}

	if (!is_tc)
	{
		*is_ours = 0;
		return NULL;
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_tc));
	if (p == NULL)
		return NULL;

	p->activate_op = TcActivate;
	/*
	 * Set these up front, so that, even if our client tries
	 * to set non-blocking mode before we're activated, or
	 * query the state of non-blocking mode, they get an error,
	 * rather than having the non-blocking mode option set
	 * for use later.
	 */
	p->getnonblock_op = TcGetNonBlock;
	p->setnonblock_op = TcSetNonBlock;
	return p;
}