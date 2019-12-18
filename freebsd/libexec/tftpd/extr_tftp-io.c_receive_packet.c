#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct tftphdr {scalar_t__ th_opcode; scalar_t__ th_code; int /*<<< orphan*/  th_msg; void* th_block; } ;
struct sockaddr_storage {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ ACK ; 
 scalar_t__ DATA ; 
 int DEBUG_PACKETS ; 
 int /*<<< orphan*/  DROPPACKETn (char*,int) ; 
 scalar_t__ ERROR ; 
 scalar_t__ EUNDEF ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int RP_ERROR ; 
 int RP_RECVFROM ; 
 int RP_TIMEOUT ; 
 int RP_TOOBIG ; 
 int RP_TOOSMALL ; 
 int RP_WRONGSOURCE ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int debug ; 
 int /*<<< orphan*/  errno ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packettype (scalar_t__) ; 
 int /*<<< orphan*/  peer_sock ; 
 int pktsize ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  timeoutpacket ; 

int
receive_packet(int peer, char *data, int size, struct sockaddr_storage *from,
    int thistimeout)
{
	struct tftphdr *pkt;
	struct sockaddr_storage from_local;
	struct sockaddr_storage *pfrom;
	socklen_t fromlen;
	int n;
	static int timed_out;

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG,
		    "Waiting %d seconds for packet", timeoutpacket);

	pkt = (struct tftphdr *)data;

	signal(SIGALRM, timeout);
	timed_out = setjmp(timeoutbuf);
	alarm(thistimeout);

	if (timed_out != 0) {
		tftp_log(LOG_ERR, "receive_packet: timeout");
		alarm(0);
		return (RP_TIMEOUT);
	}

	pfrom = (from == NULL) ? &from_local : from;
	fromlen = sizeof(*pfrom);
	n = recvfrom(peer, data, size, 0, (struct sockaddr *)pfrom, &fromlen);

	alarm(0);

	DROPPACKETn("receive_packet", RP_TIMEOUT);

	if (n < 0) {
		tftp_log(LOG_ERR, "receive_packet: timeout");
		return (RP_TIMEOUT);
	}

	if (n < 0) {
		/* No idea what could have happened if it isn't a timeout */
		tftp_log(LOG_ERR, "receive_packet: %s", strerror(errno));
		return (RP_RECVFROM);
	}
	if (n < 4) {
		tftp_log(LOG_ERR,
		    "receive_packet: packet too small (%d bytes)", n);
		return (RP_TOOSMALL);
	}

	pkt->th_opcode = ntohs((u_short)pkt->th_opcode);
	if (pkt->th_opcode == DATA ||
	    pkt->th_opcode == ACK)
		pkt->th_block = ntohs((u_short)pkt->th_block);

	if (pkt->th_opcode == DATA && n > pktsize) {
		tftp_log(LOG_ERR, "receive_packet: packet too big");
		return (RP_TOOBIG);
	}

	if (((struct sockaddr_in *)(pfrom))->sin_addr.s_addr !=
	    ((struct sockaddr_in *)(&peer_sock))->sin_addr.s_addr) {
		tftp_log(LOG_ERR,
			"receive_packet: received packet from wrong source");
		return (RP_WRONGSOURCE);
	}

	if (pkt->th_opcode == ERROR) {
		tftp_log(pkt->th_code == EUNDEF ? LOG_DEBUG : LOG_ERR,
		    "Got ERROR packet: %s", pkt->th_msg);
		return (RP_ERROR);
	}

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG, "Received %d bytes in a %s packet",
			n, packettype(pkt->th_opcode));

	return n - 4;
}