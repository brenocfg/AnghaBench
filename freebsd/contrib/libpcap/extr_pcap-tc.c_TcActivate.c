#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct pcap_tc {int /*<<< orphan*/  TcInstance; int /*<<< orphan*/ * PpiPacket; } ;
struct TYPE_13__ {int timeout; int /*<<< orphan*/  device; scalar_t__ rfmon; } ;
struct TYPE_14__ {scalar_t__ snapshot; int dlt_count; int selectable_fd; int /*<<< orphan*/  (* cleanup_op ) (TYPE_5__*) ;int /*<<< orphan*/  get_airpcap_handle_op; int /*<<< orphan*/  live_dump_ended_op; int /*<<< orphan*/  live_dump_op; int /*<<< orphan*/  setuserbuffer_op; int /*<<< orphan*/  sendqueue_transmit_op; int /*<<< orphan*/  oid_set_request_op; int /*<<< orphan*/  oid_get_request_op; int /*<<< orphan*/  getevent_op; int /*<<< orphan*/  setmintocopy_op; int /*<<< orphan*/  setmode_op; int /*<<< orphan*/  setbuff_op; int /*<<< orphan*/  stats_ex_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  set_datalink_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  errbuf; TYPE_4__ opt; int /*<<< orphan*/  inject_op; void** dlt_list; void* linktype; struct pcap_tc* priv; } ;
typedef  TYPE_5__ pcap_t ;
typedef  int ULONG ;
struct TYPE_16__ {scalar_t__ (* InstanceOpenByName ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* InstanceSetFeature ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* StatusGetString ) (scalar_t__) ;} ;
struct TYPE_12__ {int PfhLength; int /*<<< orphan*/  PfhType; } ;
struct TYPE_11__ {int PfhLength; int /*<<< orphan*/  PfhType; } ;
struct TYPE_10__ {int PphLength; scalar_t__ PphVersion; scalar_t__ PphFlags; void* PphDlt; } ;
struct TYPE_15__ {TYPE_3__ Dot3FieldHeader; TYPE_2__ AggregationFieldHeader; TYPE_1__ PacketHeader; } ;
typedef  scalar_t__ TC_STATUS ;
typedef  TYPE_6__* PPPI_HEADER ;
typedef  int /*<<< orphan*/  PPI_HEADER ;
typedef  int /*<<< orphan*/  PPI_FIELD_AGGREGATION_EXTENSION ;
typedef  int /*<<< orphan*/  PPI_FIELD_802_3_EXTENSION ;

/* Variables and functions */
 void* DLT_EN10MB ; 
 void* DLT_PPI ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int MAX_TC_PACKET_SIZE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int /*<<< orphan*/  PPI_FIELD_TYPE_802_3_EXTENSION ; 
 int /*<<< orphan*/  PPI_FIELD_TYPE_AGGREGATION_EXTENSION ; 
 int /*<<< orphan*/  TC_INST_FT_READ_TIMEOUT ; 
 int /*<<< orphan*/  TC_INST_FT_RX_STATUS ; 
 int /*<<< orphan*/  TC_INST_FT_TX_STATUS ; 
 scalar_t__ TC_SUCCESS ; 
 int /*<<< orphan*/  TcCleanup (TYPE_5__*) ; 
 int /*<<< orphan*/  TcGetAirPcapHandle ; 
 int /*<<< orphan*/  TcGetNonBlock ; 
 int /*<<< orphan*/  TcGetReceiveWaitHandle ; 
 int /*<<< orphan*/  TcInject ; 
 int /*<<< orphan*/  TcLiveDump ; 
 int /*<<< orphan*/  TcLiveDumpEnded ; 
 int /*<<< orphan*/  TcOidGetRequest ; 
 int /*<<< orphan*/  TcOidSetRequest ; 
 int /*<<< orphan*/  TcRead ; 
 int /*<<< orphan*/  TcSendqueueTransmit ; 
 int /*<<< orphan*/  TcSetBuff ; 
 int /*<<< orphan*/  TcSetDatalink ; 
 int /*<<< orphan*/  TcSetFilter ; 
 int /*<<< orphan*/  TcSetMinToCopy ; 
 int /*<<< orphan*/  TcSetMode ; 
 int /*<<< orphan*/  TcSetNonBlock ; 
 int /*<<< orphan*/  TcSetUserBuffer ; 
 int /*<<< orphan*/  TcStats ; 
 int /*<<< orphan*/  TcStatsEx ; 
 TYPE_7__ g_TcFunctions ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (scalar_t__) ; 

__attribute__((used)) static int
TcActivate(pcap_t *p)
{
	struct pcap_tc *pt = p->priv;
	TC_STATUS status;
	ULONG timeout;
	PPPI_HEADER pPpiHeader;

	if (p->opt.rfmon)
	{
		/*
		 * No monitor mode on Tc cards; they're Ethernet
		 * capture adapters.
		 */
		return PCAP_ERROR_RFMON_NOTSUP;
	}

	pt->PpiPacket = malloc(sizeof(PPI_HEADER) + MAX_TC_PACKET_SIZE);

	if (pt->PpiPacket == NULL)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "Error allocating memory");
		return PCAP_ERROR;
	}

	/*
	 * Turn a negative snapshot value (invalid), a snapshot value of
	 * 0 (unspecified), or a value bigger than the normal maximum
	 * value, into the maximum allowed value.
	 *
	 * If some application really *needs* a bigger snapshot
	 * length, we should just increase MAXIMUM_SNAPLEN.
	 */
	if (p->snapshot <= 0 || p->snapshot > MAXIMUM_SNAPLEN)
		p->snapshot = MAXIMUM_SNAPLEN;

	/*
	 * Initialize the PPI fixed fields
	 */
	pPpiHeader = (PPPI_HEADER)pt->PpiPacket;
	pPpiHeader->PacketHeader.PphDlt = DLT_EN10MB;
	pPpiHeader->PacketHeader.PphLength = sizeof(PPI_HEADER);
	pPpiHeader->PacketHeader.PphFlags = 0;
	pPpiHeader->PacketHeader.PphVersion = 0;

	pPpiHeader->AggregationFieldHeader.PfhLength = sizeof(PPI_FIELD_AGGREGATION_EXTENSION);
	pPpiHeader->AggregationFieldHeader.PfhType = PPI_FIELD_TYPE_AGGREGATION_EXTENSION;

	pPpiHeader->Dot3FieldHeader.PfhLength = sizeof(PPI_FIELD_802_3_EXTENSION);
	pPpiHeader->Dot3FieldHeader.PfhType = PPI_FIELD_TYPE_802_3_EXTENSION;

	status = g_TcFunctions.InstanceOpenByName(p->opt.device, &pt->TcInstance);

	if (status != TC_SUCCESS)
	{
		/* Adapter detected but we are not able to open it. Return failure. */
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "Error opening TurboCap adapter: %s", g_TcFunctions.StatusGetString(status));
		return PCAP_ERROR;
	}

	p->linktype = DLT_EN10MB;
	p->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
	/*
	 * If that fails, just leave the list empty.
	 */
	if (p->dlt_list != NULL) {
		p->dlt_list[0] = DLT_EN10MB;
		p->dlt_list[1] = DLT_PPI;
		p->dlt_count = 2;
	}

	/*
	 * ignore promiscuous mode
	 * p->opt.promisc
	 */


	/*
	 * ignore all the buffer sizes
	 */

	/*
	 * enable reception
	 */
	status = g_TcFunctions.InstanceSetFeature(pt->TcInstance, TC_INST_FT_RX_STATUS, 1);

	if (status != TC_SUCCESS)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,"Error enabling reception on a TurboCap instance: %s", g_TcFunctions.StatusGetString(status));
		goto bad;
	}

	/*
	 * enable transmission
	 */
	status = g_TcFunctions.InstanceSetFeature(pt->TcInstance, TC_INST_FT_TX_STATUS, 1);
	/*
	 * Ignore the error here.
	 */

	p->inject_op = TcInject;
	/*
	 * if the timeout is -1, it means immediate return, no timeout
	 * if the timeout is 0, it means INFINITE
	 */

	if (p->opt.timeout == 0)
	{
		timeout = 0xFFFFFFFF;
	}
	else
	if (p->opt.timeout < 0)
	{
		/*
		 *  we insert a minimal timeout here
		 */
		timeout = 10;
	}
	else
	{
		timeout = p->opt.timeout;
	}

	status = g_TcFunctions.InstanceSetFeature(pt->TcInstance, TC_INST_FT_READ_TIMEOUT, timeout);

	if (status != TC_SUCCESS)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,"Error setting the read timeout a TurboCap instance: %s", g_TcFunctions.StatusGetString(status));
		goto bad;
	}

	p->read_op = TcRead;
	p->setfilter_op = TcSetFilter;
	p->setdirection_op = NULL;	/* Not implemented. */
	p->set_datalink_op = TcSetDatalink;
	p->getnonblock_op = TcGetNonBlock;
	p->setnonblock_op = TcSetNonBlock;
	p->stats_op = TcStats;
#ifdef _WIN32
	p->stats_ex_op = TcStatsEx;
	p->setbuff_op = TcSetBuff;
	p->setmode_op = TcSetMode;
	p->setmintocopy_op = TcSetMinToCopy;
	p->getevent_op = TcGetReceiveWaitHandle;
	p->oid_get_request_op = TcOidGetRequest;
	p->oid_set_request_op = TcOidSetRequest;
	p->sendqueue_transmit_op = TcSendqueueTransmit;
	p->setuserbuffer_op = TcSetUserBuffer;
	p->live_dump_op = TcLiveDump;
	p->live_dump_ended_op = TcLiveDumpEnded;
	p->get_airpcap_handle_op = TcGetAirPcapHandle;
#else
	p->selectable_fd = -1;
#endif

	p->cleanup_op = TcCleanup;

	return 0;
bad:
	TcCleanup(p);
	return PCAP_ERROR;
}