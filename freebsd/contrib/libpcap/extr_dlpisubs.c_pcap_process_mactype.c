#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int offset; int* dlt_list; int dlt_count; int /*<<< orphan*/  errbuf; void* linktype; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 void* DLT_FDDI ; 
 void* DLT_IEEE802 ; 
 void* DLT_IPV4 ; 
 void* DLT_IPV6 ; 
 void* DLT_RAW ; 
 void* DLT_SUNATM ; 
#define  DL_CSMACD 135 
#define  DL_ETHER 134 
#define  DL_FDDI 133 
#define  DL_IPATM 132 
#define  DL_IPNET 131 
#define  DL_IPV4 130 
#define  DL_IPV6 129 
#define  DL_TPR 128 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
pcap_process_mactype(pcap_t *p, u_int mactype)
{
	int retv = 0;

	switch (mactype) {

	case DL_CSMACD:
	case DL_ETHER:
		p->linktype = DLT_EN10MB;
		p->offset = 2;
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
		p->dlt_list = (u_int *)malloc(sizeof(u_int) * 2);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (p->dlt_list != NULL) {
			p->dlt_list[0] = DLT_EN10MB;
			p->dlt_list[1] = DLT_DOCSIS;
			p->dlt_count = 2;
		}
		break;

	case DL_FDDI:
		p->linktype = DLT_FDDI;
		p->offset = 3;
		break;

	case DL_TPR:
		/* XXX - what about DL_TPB?  Is that Token Bus?  */
		p->linktype = DLT_IEEE802;
		p->offset = 2;
		break;

#ifdef HAVE_SOLARIS
	case DL_IPATM:
		p->linktype = DLT_SUNATM;
		p->offset = 0;  /* works for LANE and LLC encapsulation */
		break;
#endif

#ifdef DL_IPV4
	case DL_IPV4:
		p->linktype = DLT_IPV4;
		p->offset = 0;
		break;
#endif

#ifdef DL_IPV6
	case DL_IPV6:
		p->linktype = DLT_IPV6;
		p->offset = 0;
		break;
#endif

#ifdef DL_IPNET
	case DL_IPNET:
		/*
		 * XXX - DL_IPNET devices default to "raw IP" rather than
		 * "IPNET header"; see
		 *
		 *    http://seclists.org/tcpdump/2009/q1/202
		 *
		 * We'd have to do DL_IOC_IPNET_INFO to enable getting
		 * the IPNET header.
		 */
		p->linktype = DLT_RAW;
		p->offset = 0;
		break;
#endif

	default:
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "unknown mactype 0x%x",
		    mactype);
		retv = -1;
	}

	return (retv);
}