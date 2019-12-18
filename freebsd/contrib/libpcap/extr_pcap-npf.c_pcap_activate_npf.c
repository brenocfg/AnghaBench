#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct pcap_win {int rfmon_selfstart; TYPE_6__* adapter; int /*<<< orphan*/  dag_fcs_bits; } ;
struct TYPE_15__ {scalar_t__ buffer_size; scalar_t__ nocapture_local; int /*<<< orphan*/  timeout; int /*<<< orphan*/  device; scalar_t__ immediate; scalar_t__ promisc; scalar_t__ rfmon; } ;
struct TYPE_16__ {int dlt_count; scalar_t__ snapshot; int bufsize; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* cleanup_op ) (TYPE_2__*) ;int /*<<< orphan*/  get_airpcap_handle_op; int /*<<< orphan*/  live_dump_ended_op; int /*<<< orphan*/  live_dump_op; int /*<<< orphan*/  setuserbuffer_op; int /*<<< orphan*/  sendqueue_transmit_op; int /*<<< orphan*/  oid_set_request_op; int /*<<< orphan*/  oid_get_request_op; int /*<<< orphan*/  getevent_op; int /*<<< orphan*/  setmintocopy_op; int /*<<< orphan*/  setmode_op; int /*<<< orphan*/  setbuff_op; int /*<<< orphan*/  stats_ex_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  errbuf; TYPE_1__ opt; int /*<<< orphan*/ * buffer; void* linktype; void** dlt_list; struct pcap_win* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  keyname ;
struct TYPE_18__ {int Flags; int /*<<< orphan*/  hFile; int /*<<< orphan*/  DagFcsLen; } ;
struct TYPE_17__ {int LinkType; } ;
typedef  TYPE_3__ NetType ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 void* DLT_ARCNET ; 
 void* DLT_ATM_RFC1483 ; 
 void* DLT_CHDLC ; 
 void* DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 void* DLT_FDDI ; 
 void* DLT_IEEE802 ; 
 void* DLT_IEEE802_11 ; 
 void* DLT_IEEE802_11_RADIO ; 
 void* DLT_NULL ; 
 void* DLT_PPI ; 
 void* DLT_PPP_SERIAL ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int INFO_FLAG_DAG_CARD ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int NDIS_PACKET_TYPE_ALL_LOCAL ; 
 int NDIS_PACKET_TYPE_BROADCAST ; 
 int NDIS_PACKET_TYPE_DIRECTED ; 
 int NDIS_PACKET_TYPE_MULTICAST ; 
 int NDIS_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  NPF_DISABLE_LOOPBACK ; 
#define  NdisMedium802_3 140 
#define  NdisMedium802_5 139 
#define  NdisMediumArcnet878_2 138 
#define  NdisMediumArcnetRaw 137 
#define  NdisMediumAtm 136 
#define  NdisMediumBare80211 135 
#define  NdisMediumCHDLC 134 
#define  NdisMediumFddi 133 
#define  NdisMediumNull 132 
#define  NdisMediumPPPSerial 131 
#define  NdisMediumPpi 130 
#define  NdisMediumRadio80211 129 
#define  NdisMediumWan 128 
 int PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int PacketGetMonitorMode (int /*<<< orphan*/ ) ; 
 scalar_t__ PacketGetNetType (TYPE_6__*,TYPE_3__*) ; 
 TYPE_6__* PacketOpenAdapter (int /*<<< orphan*/ ) ; 
 scalar_t__ PacketSetBuff (TYPE_6__*,scalar_t__) ; 
 scalar_t__ PacketSetHwFilter (TYPE_6__*,int) ; 
 int /*<<< orphan*/  PacketSetLoopbackBehavior (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PacketSetMinToCopy (TYPE_6__*,int) ; 
 int PacketSetMonitorMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PacketSetReadTimeout (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PacketSetSnapLen (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ WIN32_DEFAULT_KERNEL_BUFFER_SIZE ; 
 int WIN32_DEFAULT_USER_BUFFER_SIZE ; 
 int /*<<< orphan*/  _strlwr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pcap_cleanup_npf (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_get_airpcap_handle_npf ; 
 int /*<<< orphan*/  pcap_getevent_npf ; 
 int /*<<< orphan*/  pcap_getnonblock_npf ; 
 int /*<<< orphan*/  pcap_inject_npf ; 
 int /*<<< orphan*/  pcap_live_dump_ended_npf ; 
 int /*<<< orphan*/  pcap_live_dump_npf ; 
 int /*<<< orphan*/  pcap_oid_get_request_npf ; 
 int /*<<< orphan*/  pcap_oid_set_request_npf ; 
 int /*<<< orphan*/  pcap_read_npf ; 
 int /*<<< orphan*/  pcap_read_win32_dag ; 
 int /*<<< orphan*/  pcap_sendqueue_transmit_npf ; 
 int /*<<< orphan*/  pcap_setbuff_npf ; 
 int /*<<< orphan*/  pcap_setfilter_npf ; 
 int /*<<< orphan*/  pcap_setfilter_win32_dag ; 
 int /*<<< orphan*/  pcap_setmintocopy_npf ; 
 int /*<<< orphan*/  pcap_setmode_npf ; 
 int /*<<< orphan*/  pcap_setnonblock_npf ; 
 int /*<<< orphan*/  pcap_setuserbuffer_npf ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  pcap_stats_ex_npf ; 
 int /*<<< orphan*/  pcap_stats_npf ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_wsockinit () ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_activate_npf(pcap_t *p)
{
	struct pcap_win *pw = p->priv;
	NetType type;
	int res;
	char errbuf[PCAP_ERRBUF_SIZE+1];

	if (p->opt.rfmon) {
		/*
		 * Monitor mode is supported on Windows Vista and later.
		 */
		if (PacketGetMonitorMode(p->opt.device) == 1)
		{
			pw->rfmon_selfstart = 0;
		}
		else
		{
			if ((res = PacketSetMonitorMode(p->opt.device, 1)) != 1)
			{
				pw->rfmon_selfstart = 0;
				// Monitor mode is not supported.
				if (res == 0)
				{
					return PCAP_ERROR_RFMON_NOTSUP;
				}
				else
				{
					return PCAP_ERROR;
				}
			}
			else
			{
				pw->rfmon_selfstart = 1;
			}
		}
	}

	/* Init WinSock */
	pcap_wsockinit();

	pw->adapter = PacketOpenAdapter(p->opt.device);

	if (pw->adapter == NULL)
	{
		/* Adapter detected but we are not able to open it. Return failure. */
		pcap_win32_err_to_str(GetLastError(), errbuf);
		if (pw->rfmon_selfstart)
		{
			PacketSetMonitorMode(p->opt.device, 0);
		}
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error opening adapter: %s", errbuf);
		return (PCAP_ERROR);
	}

	/*get network type*/
	if(PacketGetNetType (pw->adapter,&type) == FALSE)
	{
		pcap_win32_err_to_str(GetLastError(), errbuf);
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Cannot determine the network type: %s", errbuf);
		goto bad;
	}

	/*Set the linktype*/
	switch (type.LinkType)
	{
	case NdisMediumWan:
		p->linktype = DLT_EN10MB;
		break;

	case NdisMedium802_3:
		p->linktype = DLT_EN10MB;
		/*
		 * This is (presumably) a real Ethernet capture; give it a
		 * link-layer-type list with DLT_EN10MB and DLT_DOCSIS, so
		 * that an application can let you choose it, in case you're
		 * capturing DOCSIS traffic that a Cisco Cable Modem
		 * Termination System is putting out onto an Ethernet (it
		 * doesn't put an Ethernet header onto the wire, it puts raw
		 * DOCSIS frames out on the wire inside the low-level
		 * Ethernet framing).
		 */
		p->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (p->dlt_list != NULL) {
			p->dlt_list[0] = DLT_EN10MB;
			p->dlt_list[1] = DLT_DOCSIS;
			p->dlt_count = 2;
		}
		break;

	case NdisMediumFddi:
		p->linktype = DLT_FDDI;
		break;

	case NdisMedium802_5:
		p->linktype = DLT_IEEE802;
		break;

	case NdisMediumArcnetRaw:
		p->linktype = DLT_ARCNET;
		break;

	case NdisMediumArcnet878_2:
		p->linktype = DLT_ARCNET;
		break;

	case NdisMediumAtm:
		p->linktype = DLT_ATM_RFC1483;
		break;

	case NdisMediumCHDLC:
		p->linktype = DLT_CHDLC;
		break;

	case NdisMediumPPPSerial:
		p->linktype = DLT_PPP_SERIAL;
		break;

	case NdisMediumNull:
		p->linktype = DLT_NULL;
		break;

	case NdisMediumBare80211:
		p->linktype = DLT_IEEE802_11;
		break;

	case NdisMediumRadio80211:
		p->linktype = DLT_IEEE802_11_RADIO;
		break;

	case NdisMediumPpi:
		p->linktype = DLT_PPI;
		break;

	default:
		p->linktype = DLT_EN10MB;			/*an unknown adapter is assumed to be ethernet*/
		break;
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

	/* Set promiscuous mode */
	if (p->opt.promisc)
	{

		if (PacketSetHwFilter(pw->adapter,NDIS_PACKET_TYPE_PROMISCUOUS) == FALSE)
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "failed to set hardware filter to promiscuous mode");
			goto bad;
		}
	}
	else
	{
		/* NDIS_PACKET_TYPE_ALL_LOCAL selects "All packets sent by installed
		 * protocols and all packets indicated by the NIC" but if no protocol
		 * drivers (like TCP/IP) are installed, NDIS_PACKET_TYPE_DIRECTED,
		 * NDIS_PACKET_TYPE_BROADCAST, and NDIS_PACKET_TYPE_MULTICAST are needed to
		 * capture incoming frames.
		 */
		if (PacketSetHwFilter(pw->adapter,
			NDIS_PACKET_TYPE_ALL_LOCAL |
			NDIS_PACKET_TYPE_DIRECTED |
			NDIS_PACKET_TYPE_BROADCAST |
			NDIS_PACKET_TYPE_MULTICAST) == FALSE)
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "failed to set hardware filter to non-promiscuous mode");
			goto bad;
		}
	}

	/* Set the buffer size */
	p->bufsize = WIN32_DEFAULT_USER_BUFFER_SIZE;

	if(!(pw->adapter->Flags & INFO_FLAG_DAG_CARD))
	{
	/*
	 * Traditional Adapter
	 */
		/*
		 * If the buffer size wasn't explicitly set, default to
		 * WIN32_DEFAULT_KERNEL_BUFFER_SIZE.
		 */
	 	if (p->opt.buffer_size == 0)
	 		p->opt.buffer_size = WIN32_DEFAULT_KERNEL_BUFFER_SIZE;

		if(PacketSetBuff(pw->adapter,p->opt.buffer_size)==FALSE)
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "driver error: not enough memory to allocate the kernel buffer");
			goto bad;
		}

		p->buffer = malloc(p->bufsize);
		if (p->buffer == NULL)
		{
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "malloc");
			goto bad;
		}

		if (p->opt.immediate)
		{
			/* tell the driver to copy the buffer as soon as data arrives */
			if(PacketSetMinToCopy(pw->adapter,0)==FALSE)
			{
				pcap_win32_err_to_str(GetLastError(), errbuf);
				pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
				    "Error calling PacketSetMinToCopy: %s",
				    errbuf);
				goto bad;
			}
		}
		else
		{
			/* tell the driver to copy the buffer only if it contains at least 16K */
			if(PacketSetMinToCopy(pw->adapter,16000)==FALSE)
			{
				pcap_win32_err_to_str(GetLastError(), errbuf);
				pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
				    "Error calling PacketSetMinToCopy: %s",
				    errbuf);
				goto bad;
			}
		}
	} else {
		/*
		 * Dag Card
		 */
#ifdef HAVE_DAG_API
		/*
		 * We have DAG support.
		 */
		LONG	status;
		HKEY	dagkey;
		DWORD	lptype;
		DWORD	lpcbdata;
		int		postype = 0;
		char	keyname[512];

		pcap_snprintf(keyname, sizeof(keyname), "%s\\CardParams\\%s",
			"SYSTEM\\CurrentControlSet\\Services\\DAG",
			strstr(_strlwr(p->opt.device), "dag"));
		do
		{
			status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyname, 0, KEY_READ, &dagkey);
			if(status != ERROR_SUCCESS)
				break;

			status = RegQueryValueEx(dagkey,
				"PosType",
				NULL,
				&lptype,
				(char*)&postype,
				&lpcbdata);

			if(status != ERROR_SUCCESS)
			{
				postype = 0;
			}

			RegCloseKey(dagkey);
		}
		while(FALSE);


		p->snapshot = PacketSetSnapLen(pw->adapter, p->snapshot);

		/* Set the length of the FCS associated to any packet. This value
		 * will be subtracted to the packet length */
		pw->dag_fcs_bits = pw->adapter->DagFcsLen;
#else /* HAVE_DAG_API */
		/*
		 * No DAG support.
		 */
		goto bad;
#endif /* HAVE_DAG_API */
	}

	PacketSetReadTimeout(pw->adapter, p->opt.timeout);

	/* disable loopback capture if requested */
	if (p->opt.nocapture_local)
	{
		if (!PacketSetLoopbackBehavior(pw->adapter, NPF_DISABLE_LOOPBACK))
		{
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "Unable to disable the capture of loopback packets.");
			goto bad;
		}
	}

#ifdef HAVE_DAG_API
	if(pw->adapter->Flags & INFO_FLAG_DAG_CARD)
	{
		/* install dag specific handlers for read and setfilter */
		p->read_op = pcap_read_win32_dag;
		p->setfilter_op = pcap_setfilter_win32_dag;
	}
	else
	{
#endif /* HAVE_DAG_API */
		/* install traditional npf handlers for read and setfilter */
		p->read_op = pcap_read_npf;
		p->setfilter_op = pcap_setfilter_npf;
#ifdef HAVE_DAG_API
	}
#endif /* HAVE_DAG_API */
	p->setdirection_op = NULL;	/* Not implemented. */
	    /* XXX - can this be implemented on some versions of Windows? */
	p->inject_op = pcap_inject_npf;
	p->set_datalink_op = NULL;	/* can't change data link type */
	p->getnonblock_op = pcap_getnonblock_npf;
	p->setnonblock_op = pcap_setnonblock_npf;
	p->stats_op = pcap_stats_npf;
	p->stats_ex_op = pcap_stats_ex_npf;
	p->setbuff_op = pcap_setbuff_npf;
	p->setmode_op = pcap_setmode_npf;
	p->setmintocopy_op = pcap_setmintocopy_npf;
	p->getevent_op = pcap_getevent_npf;
	p->oid_get_request_op = pcap_oid_get_request_npf;
	p->oid_set_request_op = pcap_oid_set_request_npf;
	p->sendqueue_transmit_op = pcap_sendqueue_transmit_npf;
	p->setuserbuffer_op = pcap_setuserbuffer_npf;
	p->live_dump_op = pcap_live_dump_npf;
	p->live_dump_ended_op = pcap_live_dump_ended_npf;
	p->get_airpcap_handle_op = pcap_get_airpcap_handle_npf;
	p->cleanup_op = pcap_cleanup_npf;

	/*
	 * XXX - this is only done because WinPcap supported
	 * pcap_fileno() returning the hFile HANDLE from the
	 * ADAPTER structure.  We make no general guarantees
	 * that the caller can do anything useful with it.
	 *
	 * (Not that we make any general guarantee of that
	 * sort on UN*X, either, any more, given that not
	 * all capture devices are regular OS network
	 * interfaces.)
	 */
	p->handle = pw->adapter->hFile;

	return (0);
bad:
	pcap_cleanup_npf(p);
	return (PCAP_ERROR);
}