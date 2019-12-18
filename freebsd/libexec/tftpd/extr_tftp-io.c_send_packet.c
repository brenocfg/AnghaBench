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
typedef  int /*<<< orphan*/  uint16_t ;
struct tftphdr {int /*<<< orphan*/  th_opcode; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROPPACKETn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packettype (int /*<<< orphan*/ ) ; 
 TYPE_1__ peer_sock ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
send_packet(int peer, uint16_t block, char *pkt, int size)
{
	int i;
	int t = 1;

	for (i = 0; i < 12 ; i++) {
		DROPPACKETn("send_packet", 0);

		if (sendto(peer, pkt, size, 0, (struct sockaddr *)&peer_sock,
		    peer_sock.ss_len) == size) {
			if (i)
				tftp_log(LOG_ERR,
				    "%s block %d, attempt %d successful",
		    		    packettype(ntohs(((struct tftphdr *)
				    (pkt))->th_opcode)), block, i);
			return (0);
		}
		tftp_log(LOG_ERR,
		    "%s block %d, attempt %d failed (Error %d: %s)", 
		    packettype(ntohs(((struct tftphdr *)(pkt))->th_opcode)),
		    block, i, errno, strerror(errno));
		sleep(t);
		if (t < 32)
			t <<= 1;
	}
	tftp_log(LOG_ERR, "send_packet: %s", strerror(errno));
	return (1);
}