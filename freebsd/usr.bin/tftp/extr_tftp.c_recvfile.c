#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
struct tftphdr {scalar_t__ th_opcode; int /*<<< orphan*/  th_stuff; int /*<<< orphan*/  th_msg; int /*<<< orphan*/  th_code; } ;
struct tftp_stats {scalar_t__ amount; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int DEBUG_SIMPLE ; 
 int /*<<< orphan*/  EBADOP ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAXPKTSIZE ; 
 scalar_t__ OACK ; 
 int RP_TIMEOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int debug ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_rfc_enabled ; 
 int /*<<< orphan*/  parse_options (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  peer_sock ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printstats (char*,int /*<<< orphan*/ ,struct tftp_stats*) ; 
 int receive_packet (int,char*,int,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int send_ack (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 int send_rrq (int,char*,char*) ; 
 int /*<<< orphan*/  stats_init (struct tftp_stats*) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_receive (int,int*,struct tftp_stats*,struct tftphdr*,int) ; 
 int /*<<< orphan*/  timeoutpacket ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  warn (char*) ; 
 scalar_t__ write_init (int,int /*<<< orphan*/ *,char*) ; 

void
recvfile(int peer, char *port, int fd, char *name, char *mode)
{
	struct tftphdr *rp;
	uint16_t block;
	char recvbuffer[MAXPKTSIZE];
	int n, i;
	struct tftp_stats tftp_stats;

	stats_init(&tftp_stats);

	rp = (struct tftphdr *)recvbuffer;

	if (port == NULL) {
		struct servent *se;
		se = getservbyname("tftp", "udp");
		assert(se != NULL);
		((struct sockaddr_in *)&peer_sock)->sin_port = se->s_port;
	} else
		((struct sockaddr_in *)&peer_sock)->sin_port =
		    htons(atoi(port));

	for (i = 0; i < 12; i++) {
		struct sockaddr_storage from;

		/* Tell the other side what we want to do */
		if (debug&DEBUG_SIMPLE)
			printf("Requesting %s\n", name);

		n = send_rrq(peer, name, mode);
		if (n > 0) {
			printf("Cannot send RRQ packet\n");
			return;
		}

		/*
		 * The first packet we receive has the new destination port
		 * we have to send the next packets to.
		 */
		n = receive_packet(peer, recvbuffer,
		    MAXPKTSIZE, &from, timeoutpacket);

		/* We got something useful! */
		if (n >= 0) {
			((struct sockaddr_in *)&peer_sock)->sin_port =
			    ((struct sockaddr_in *)&from)->sin_port;
			break;
		}

		/* We should retry if this happens */
		if (n == RP_TIMEOUT) {
			printf("Try %d, didn't receive answer from remote.\n",
			    i + 1);
			continue;
		}

		/* Otherwise it is a fatal error */
		break;
	}
	if (i == 12) {
		printf("Transfer timed out.\n");
		return;
	}
	if (rp->th_opcode == ERROR) {
		tftp_log(LOG_ERR, "Error code %d: %s", rp->th_code, rp->th_msg);
		return;
	}

	if (write_init(fd, NULL, mode) < 0) {
		warn("write_init");
		return;
	}

	/*
	 * If the first packet is an OACK packet instead of an DATA packet,
	 * handle it different.
	 */
	if (rp->th_opcode == OACK) {
		if (!options_rfc_enabled) {
			printf("Got OACK while options are not enabled!\n");
			send_error(peer, EBADOP);
			return;
		}

		parse_options(peer, rp->th_stuff, n + 2);

		n = send_ack(peer, 0);
		if (n > 0) {
			printf("Cannot send ACK on OACK.\n");
			return;
		}
		block = 0;
		tftp_receive(peer, &block, &tftp_stats, NULL, 0);
	} else {
		block = 1;
		tftp_receive(peer, &block, &tftp_stats, rp, n);
	}

	if (tftp_stats.amount > 0)
		printstats("Received", verbose, &tftp_stats);
	return;
}