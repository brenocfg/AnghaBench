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
struct tftphdr {scalar_t__ th_opcode; int /*<<< orphan*/  th_stuff; } ;
struct tftp_stats {scalar_t__ amount; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct servent {int /*<<< orphan*/  s_port; } ;
typedef  int /*<<< orphan*/  serv ;

/* Variables and functions */
 int DEBUG_SIMPLE ; 
 int /*<<< orphan*/  EBADOP ; 
 scalar_t__ ERROR ; 
 int MAXPKTSIZE ; 
 scalar_t__ OACK ; 
 int RP_TIMEOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int debug ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  options_rfc_enabled ; 
 int /*<<< orphan*/  parse_options (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  peer_sock ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printstats (char*,int /*<<< orphan*/ ,struct tftp_stats*) ; 
 int /*<<< orphan*/  read_close () ; 
 scalar_t__ read_init (int,int /*<<< orphan*/ *,char*) ; 
 int receive_packet (int,char*,int,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 int send_wrq (int,char*,char*) ; 
 int /*<<< orphan*/  stats_init (struct tftp_stats*) ; 
 int /*<<< orphan*/  tftp_send (int,int*,struct tftp_stats*) ; 
 int /*<<< orphan*/  timeoutpacket ; 
 int txrx_error ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  warn (char*) ; 

void
xmitfile(int peer, char *port, int fd, char *name, char *mode)
{
	struct tftphdr *rp;
	int n, i;
	uint16_t block;
	struct sockaddr_storage serv;	/* valid server port number */
	char recvbuffer[MAXPKTSIZE];
	struct tftp_stats tftp_stats;

	stats_init(&tftp_stats);

	memset(&serv, 0, sizeof(serv));
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
			printf("Sending %s\n", name);

		n = send_wrq(peer, name, mode);
		if (n > 0) {
			printf("Cannot send WRQ packet\n");
			return;
		}

		/*
		 * The first packet we receive has the new destination port
		 * we have to send the next packets to.
		 */
		n = receive_packet(peer, recvbuffer,
		    MAXPKTSIZE, &from, timeoutpacket);

		/* We got some data! */
		if (n >= 0) {
			((struct sockaddr_in *)&peer_sock)->sin_port =
			    ((struct sockaddr_in *)&from)->sin_port;
			break;
		}

		/* This should be retried */
		if (n == RP_TIMEOUT) {
			printf("Try %d, didn't receive answer from remote.\n",
			    i + 1);
			continue;
		}

		/* Everything else is fatal */
		break;
	}
	if (i == 12) {
		printf("Transfer timed out.\n");
		return;
	}
	if (rp->th_opcode == ERROR) {
		printf("Got ERROR, aborted\n");
		return;
	}

	/*
	 * If the first packet is an OACK instead of an ACK packet,
	 * handle it different.
	 */
	if (rp->th_opcode == OACK) {
		if (!options_rfc_enabled) {
			printf("Got OACK while options are not enabled!\n");
			send_error(peer, EBADOP);
			return;
		}

		parse_options(peer, rp->th_stuff, n + 2);
	}

	if (read_init(fd, NULL, mode) < 0) {
		warn("read_init()");
		return;
	}

	block = 1;
	tftp_send(peer, &block, &tftp_stats);

	read_close();
	if (tftp_stats.amount > 0)
		printstats("Sent", verbose, &tftp_stats);

	txrx_error = 1;
}