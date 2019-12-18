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
struct pcap_tc {int /*<<< orphan*/  TcAcceptedCount; int /*<<< orphan*/  TcInstance; } ;
struct pcap_stat {int ps_recv; int ps_ifdrop; int ps_drop; int /*<<< orphan*/  ps_capt; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_4__ {int /*<<< orphan*/  errbuf; struct pcap_tc* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  scalar_t__ ULONGLONG ;
typedef  void* ULONG ;
struct TYPE_5__ {scalar_t__ (* InstanceQueryStatistics ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* StatisticsQueryValue ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* StatusGetString ) (scalar_t__) ;} ;
typedef  scalar_t__ TC_STATUS ;
typedef  int /*<<< orphan*/  TC_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  TC_COUNTER_INSTANCE_RX_DROPPED_PACKETS ; 
 int /*<<< orphan*/  TC_COUNTER_INSTANCE_TOTAL_RX_PACKETS ; 
 scalar_t__ TC_SUCCESS ; 
 TYPE_2__ g_TcFunctions ; 
 int /*<<< orphan*/  memset (struct pcap_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub6 (scalar_t__) ; 

__attribute__((used)) static int
TcStats(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_tc *pt = p->priv;
	TC_STATISTICS statistics;
	TC_STATUS status;
	ULONGLONG counter;
	struct pcap_stat s;

	status = g_TcFunctions.InstanceQueryStatistics(pt->TcInstance, &statistics);

	if (status != TC_SUCCESS)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "TurboCap error in TcInstanceQueryStatistics: %s (%08x)", g_TcFunctions.StatusGetString(status), status);
		return -1;
	}

	memset(&s, 0, sizeof(s));

	status = g_TcFunctions.StatisticsQueryValue(statistics, TC_COUNTER_INSTANCE_TOTAL_RX_PACKETS, &counter);
	if (status != TC_SUCCESS)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "TurboCap error in TcStatisticsQueryValue: %s (%08x)", g_TcFunctions.StatusGetString(status), status);
		return -1;
	}
	if (counter <= (ULONGLONG)0xFFFFFFFF)
	{
		s.ps_recv = (ULONG)counter;
	}
	else
	{
		s.ps_recv = 0xFFFFFFFF;
	}

	status = g_TcFunctions.StatisticsQueryValue(statistics, TC_COUNTER_INSTANCE_RX_DROPPED_PACKETS, &counter);
	if (status != TC_SUCCESS)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "TurboCap error in TcStatisticsQueryValue: %s (%08x)", g_TcFunctions.StatusGetString(status), status);
		return -1;
	}
	if (counter <= (ULONGLONG)0xFFFFFFFF)
	{
		s.ps_ifdrop = (ULONG)counter;
		s.ps_drop = (ULONG)counter;
	}
	else
	{
		s.ps_ifdrop = 0xFFFFFFFF;
		s.ps_drop = 0xFFFFFFFF;
	}

#if defined(_WIN32) && defined(ENABLE_REMOTE)
	s.ps_capt = pt->TcAcceptedCount;
#endif
	*ps = s;

	return 0;
}