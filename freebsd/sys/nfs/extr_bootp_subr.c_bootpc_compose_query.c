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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vendor_client ;
typedef  int uint8_t ;
typedef  unsigned char uint32_t ;
struct thread {int dummy; } ;
struct TYPE_5__ {int htype; unsigned char* vend; int /*<<< orphan*/  flags; scalar_t__ secs; int /*<<< orphan*/  chaddr; int /*<<< orphan*/  xid; scalar_t__ hops; int /*<<< orphan*/  hlen; int /*<<< orphan*/  op; } ;
struct TYPE_4__ {unsigned char yiaddr; } ;
struct bootpc_ifcontext {int state; unsigned char dhcpserver; TYPE_2__ call; int /*<<< orphan*/  gotdhcpserver; TYPE_1__ reply; void* dhcpquerytype; TYPE_3__* sdl; int /*<<< orphan*/  xid; scalar_t__ gotrootpath; } ;
struct bootp_packet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  sdl_alen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTP_REQUEST ; 
 void* DHCP_DISCOVER ; 
 void* DHCP_NOMSG ; 
 void* DHCP_REQUEST ; 
#define  IF_DHCP_OFFERED 129 
#define  IF_DHCP_UNRESOLVED 128 
 int /*<<< orphan*/  LLADDR (TYPE_3__*) ; 
 char* MACHINE ; 
 int /*<<< orphan*/  TAG_DHCP_LEASETIME ; 
 void* TAG_DHCP_MSGTYPE ; 
 int /*<<< orphan*/  TAG_DHCP_REQ_ADDR ; 
 int /*<<< orphan*/  TAG_DHCP_SERVERID ; 
 unsigned char TAG_END ; 
 int /*<<< orphan*/  TAG_MAXMSGSIZE ; 
 int /*<<< orphan*/  TAG_VENDOR_INDENTIFIER ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bootpc_ifctx_isunresolved (struct bootpc_ifcontext*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 unsigned char htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 char* osrelease ; 
 char* ostype ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,char*,char*,char*) ; 
 int strlen (unsigned char*) ; 
 int /*<<< orphan*/  txdr_unsigned (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bootpc_compose_query(struct bootpc_ifcontext *ifctx, struct thread *td)
{
	unsigned char *vendp;
	unsigned char vendor_client[64];
	uint32_t leasetime;
	uint8_t vendor_client_len;

	ifctx->gotrootpath = 0;

	bzero((caddr_t) &ifctx->call, sizeof(ifctx->call));

	/* bootpc part */
	ifctx->call.op = BOOTP_REQUEST; 	/* BOOTREQUEST */
	ifctx->call.htype = 1;			/* 10mb ethernet */
	ifctx->call.hlen = ifctx->sdl->sdl_alen;/* Hardware address length */
	ifctx->call.hops = 0;
	if (bootpc_ifctx_isunresolved(ifctx) != 0)
		ifctx->xid++;
	ifctx->call.xid = txdr_unsigned(ifctx->xid);
	bcopy(LLADDR(ifctx->sdl), &ifctx->call.chaddr, ifctx->sdl->sdl_alen);

	vendp = ifctx->call.vend;
	*vendp++ = 99;		/* RFC1048 cookie */
	*vendp++ = 130;
	*vendp++ = 83;
	*vendp++ = 99;
	*vendp++ = TAG_MAXMSGSIZE;
	*vendp++ = 2;
	*vendp++ = (sizeof(struct bootp_packet) >> 8) & 255;
	*vendp++ = sizeof(struct bootp_packet) & 255;

	snprintf(vendor_client, sizeof(vendor_client), "%s:%s:%s",
		ostype, MACHINE, osrelease);
	vendor_client_len = strlen(vendor_client);
	*vendp++ = TAG_VENDOR_INDENTIFIER;
	*vendp++ = vendor_client_len;
	memcpy(vendp, vendor_client, vendor_client_len);
	vendp += vendor_client_len;
	ifctx->dhcpquerytype = DHCP_NOMSG;
	switch (ifctx->state) {
	case IF_DHCP_UNRESOLVED:
		*vendp++ = TAG_DHCP_MSGTYPE;
		*vendp++ = 1;
		*vendp++ = DHCP_DISCOVER;
		ifctx->dhcpquerytype = DHCP_DISCOVER;
		ifctx->gotdhcpserver = 0;
		break;
	case IF_DHCP_OFFERED:
		*vendp++ = TAG_DHCP_MSGTYPE;
		*vendp++ = 1;
		*vendp++ = DHCP_REQUEST;
		ifctx->dhcpquerytype = DHCP_REQUEST;
		*vendp++ = TAG_DHCP_REQ_ADDR;
		*vendp++ = 4;
		memcpy(vendp, &ifctx->reply.yiaddr, 4);
		vendp += 4;
		if (ifctx->gotdhcpserver != 0) {
			*vendp++ = TAG_DHCP_SERVERID;
			*vendp++ = 4;
			memcpy(vendp, &ifctx->dhcpserver, 4);
			vendp += 4;
		}
		*vendp++ = TAG_DHCP_LEASETIME;
		*vendp++ = 4;
		leasetime = htonl(300);
		memcpy(vendp, &leasetime, 4);
		vendp += 4;
		break;
	default:
		break;
	}
	*vendp = TAG_END;

	ifctx->call.secs = 0;
	ifctx->call.flags = htons(0x8000); /* We need a broadcast answer */
}