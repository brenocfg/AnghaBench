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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u_short ;
struct tftphdr {void* th_block; void* th_opcode; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  ss_len; } ;

/* Variables and functions */
 scalar_t__ ACK ; 
 int DEBUG_PACKETS ; 
 int /*<<< orphan*/  DROPPACKETn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAXPKTSIZE ; 
 int debug ; 
 int /*<<< orphan*/  errno ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_1__ peer_sock ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
send_ack(int fp, uint16_t block)
{
	struct tftphdr *tp;
	int size;
	char buf[MAXPKTSIZE];

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG, "Sending ACK for block %d", block);

	DROPPACKETn("send_ack", 0);

	tp = (struct tftphdr *)buf;
	size = sizeof(buf) - 2;
	tp->th_opcode = htons((u_short)ACK);
	tp->th_block = htons((u_short)block);
	size = 4;

	if (sendto(fp, buf, size, 0,
	    (struct sockaddr *)&peer_sock, peer_sock.ss_len) != size) {
		tftp_log(LOG_INFO, "send_ack: %s", strerror(errno));
		return (1);
	}

	return (0);
}