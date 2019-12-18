#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct tftphdr {int /*<<< orphan*/  th_opcode; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {char* o_type; int /*<<< orphan*/ * o_reply; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_len; } ;

/* Variables and functions */
 int DEBUG_PACKETS ; 
 int /*<<< orphan*/  DROPPACKETn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAXPKTSIZE ; 
 scalar_t__ OACK ; 
 int debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* options ; 
 TYPE_1__ peer_sock ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,...) ; 

int
send_oack(int peer)
{
	struct tftphdr *tp;
	int size, i, n;
	char *bp;
	char buf[MAXPKTSIZE];

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG, "Sending OACK");

	DROPPACKETn("send_oack", 0);

	/*
	 * Send back an options acknowledgement (only the ones with
	 * a reply for)
	 */
	tp = (struct tftphdr *)buf;
	bp = buf + 2;
	size = sizeof(buf) - 2;
	tp->th_opcode = htons((u_short)OACK);
	for (i = 0; options[i].o_type != NULL; i++) {
		if (options[i].o_reply != NULL) {
			n = snprintf(bp, size, "%s%c%s", options[i].o_type,
				     0, options[i].o_reply);
			bp += n+1;
			size -= n+1;
			if (size < 0) {
				tftp_log(LOG_ERR, "oack: buffer overflow");
				exit(1);
			}
		}
	}
	size = bp - buf;

	if (sendto(peer, buf, size, 0,
		(struct sockaddr *)&peer_sock, peer_sock.ss_len) != size) {
		tftp_log(LOG_INFO, "send_oack: %s", strerror(errno));
		return (1);
	}

	return (0);
}