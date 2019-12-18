#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcap_tc {TYPE_6__* PpiPacket; int /*<<< orphan*/  TcAcceptedCount; int /*<<< orphan*/ * TcPacketsBuffer; int /*<<< orphan*/  TcInstance; } ;
struct TYPE_22__ {void* tv_usec; void* tv_sec; } ;
struct pcap_pkthdr {scalar_t__ len; scalar_t__ caplen; TYPE_2__ ts; } ;
struct TYPE_21__ {scalar_t__ bf_insns; } ;
struct TYPE_25__ {scalar_t__ linktype; TYPE_1__ fcode; int /*<<< orphan*/  errbuf; scalar_t__ break_loop; struct pcap_tc* priv; } ;
typedef  TYPE_5__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,TYPE_6__*) ;
typedef  void* bpf_u_int32 ;
typedef  int ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_27__ {scalar_t__ CapturedLength; int Timestamp; int Flags; scalar_t__ Length; int /*<<< orphan*/  Errors; } ;
struct TYPE_24__ {scalar_t__ Flags; int /*<<< orphan*/  Errors; } ;
struct TYPE_23__ {int /*<<< orphan*/  InterfaceId; } ;
struct TYPE_26__ {TYPE_4__ Dot3Field; TYPE_3__ AggregationField; } ;
struct TYPE_20__ {scalar_t__ (* InstanceReceivePackets ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;scalar_t__ (* PacketsBufferQueryNextPacket ) (int /*<<< orphan*/ *,TYPE_7__*,TYPE_6__**) ;int /*<<< orphan*/  (* StatusGetString ) (scalar_t__) ;int /*<<< orphan*/  (* PacketsBufferDestroy ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ TC_STATUS ;
typedef  TYPE_7__ TC_PACKET_HEADER ;
typedef  TYPE_6__* PVOID ;
typedef  TYPE_6__* PPPI_HEADER ;
typedef  int /*<<< orphan*/  PPI_HEADER ;

/* Variables and functions */
 scalar_t__ DLT_EN10MB ; 
 scalar_t__ MAX_TC_PACKET_SIZE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ PPI_FLD_802_3_EXT_FLAG_FCS_PRESENT ; 
 scalar_t__ TC_ERROR_END_OF_BUFFER ; 
 int TC_PH_FLAGS_CHECKSUM ; 
 int /*<<< orphan*/  TC_PH_FLAGS_RX_PORT_ID (int) ; 
 scalar_t__ TC_SUCCESS ; 
 scalar_t__ TRUE ; 
 scalar_t__ bpf_filter (scalar_t__,TYPE_6__*,scalar_t__,scalar_t__) ; 
 TYPE_16__ g_TcFunctions ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,TYPE_7__*,TYPE_6__**) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (scalar_t__) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,struct pcap_pkthdr*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,struct pcap_pkthdr*,TYPE_6__*) ; 

__attribute__((used)) static int TcRead(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_tc *pt = p->priv;
	TC_STATUS status;
	int n = 0;

	/*
	 * Has "pcap_breakloop()" been called?
	 */
	if (p->break_loop)
	{
		/*
		 * Yes - clear the flag that indicates that it
		 * has, and return -2 to indicate that we were
		 * told to break out of the loop.
		 */
		p->break_loop = 0;
		return -2;
	}

	if (pt->TcPacketsBuffer == NULL)
	{
		status = g_TcFunctions.InstanceReceivePackets(pt->TcInstance, &pt->TcPacketsBuffer);
		if (status != TC_SUCCESS)
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "read error, TcInstanceReceivePackets failure: %s (%08x)", g_TcFunctions.StatusGetString(status), status);
			return -1;
		}
	}

	while (TRUE)
	{
		struct pcap_pkthdr hdr;
		TC_PACKET_HEADER tcHeader;
		PVOID data;
		ULONG filterResult;

		/*
		 * Has "pcap_breakloop()" been called?
		 * If so, return immediately - if we haven't read any
		 * packets, clear the flag and return -2 to indicate
		 * that we were told to break out of the loop, otherwise
		 * leave the flag set, so that the *next* call will break
		 * out of the loop without having read any packets, and
		 * return the number of packets we've processed so far.
		 */
		if (p->break_loop)
		{
			if (n == 0)
			{
				p->break_loop = 0;
				return -2;
			}
			else
			{
				return n;
			}
		}

		if (pt->TcPacketsBuffer == NULL)
		{
			break;
		}

		status = g_TcFunctions.PacketsBufferQueryNextPacket(pt->TcPacketsBuffer, &tcHeader, &data);

		if (status == TC_ERROR_END_OF_BUFFER)
		{
			g_TcFunctions.PacketsBufferDestroy(pt->TcPacketsBuffer);
			pt->TcPacketsBuffer = NULL;
			break;
		}

		if (status != TC_SUCCESS)
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "read error, TcPacketsBufferQueryNextPacket failure: %s (%08x)", g_TcFunctions.StatusGetString(status), status);
			return -1;
		}

		/* No underlaying filtering system. We need to filter on our own */
		if (p->fcode.bf_insns)
		{
			filterResult = bpf_filter(p->fcode.bf_insns, data, tcHeader.Length, tcHeader.CapturedLength);

			if (filterResult == 0)
			{
				continue;
			}

			if (filterResult > tcHeader.CapturedLength)
			{
				filterResult = tcHeader.CapturedLength;
			}
		}
		else
		{
			filterResult = tcHeader.CapturedLength;
		}

		pt->TcAcceptedCount ++;

		hdr.ts.tv_sec = (bpf_u_int32)(tcHeader.Timestamp / (ULONGLONG)(1000  * 1000 * 1000));
		hdr.ts.tv_usec = (bpf_u_int32)((tcHeader.Timestamp % (ULONGLONG)(1000  * 1000 * 1000)) / 1000);

		if (p->linktype == DLT_EN10MB)
		{
			hdr.caplen = filterResult;
			hdr.len = tcHeader.Length;
			(*callback)(user, &hdr, data);
		}
		else
		{
			PPPI_HEADER pPpiHeader = (PPPI_HEADER)pt->PpiPacket;
			PVOID data2 = pPpiHeader + 1;

			pPpiHeader->AggregationField.InterfaceId = TC_PH_FLAGS_RX_PORT_ID(tcHeader.Flags);
			pPpiHeader->Dot3Field.Errors = tcHeader.Errors;
			if (tcHeader.Flags & TC_PH_FLAGS_CHECKSUM)
			{
				pPpiHeader->Dot3Field.Flags = PPI_FLD_802_3_EXT_FLAG_FCS_PRESENT;
			}
			else
			{
				pPpiHeader->Dot3Field.Flags = 0;
			}

			if (filterResult <= MAX_TC_PACKET_SIZE)
			{
				memcpy(data2, data, filterResult);
				hdr.caplen = sizeof(PPI_HEADER) + filterResult;
				hdr.len = sizeof(PPI_HEADER) + tcHeader.Length;
			}
			else
			{
				memcpy(data2, data, MAX_TC_PACKET_SIZE);
				hdr.caplen = sizeof(PPI_HEADER) + MAX_TC_PACKET_SIZE;
				hdr.len = sizeof(PPI_HEADER) + tcHeader.Length;
			}

			(*callback)(user, &hdr, pt->PpiPacket);

		}

		if (++n >= cnt && cnt > 0)
		{
			return n;
		}
	}

	return n;
}