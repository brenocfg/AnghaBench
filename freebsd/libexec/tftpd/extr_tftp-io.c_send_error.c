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
struct tftphdr {char* th_msg; void* th_code; void* th_opcode; } ;
struct sockaddr {int dummy; } ;
struct errmsg {int e_code; int e_msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_len; } ;

/* Variables and functions */
 int DEBUG_PACKETS ; 
 int /*<<< orphan*/  DROPPACKET (char*) ; 
 scalar_t__ ERROR ; 
 void* EUNDEF ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAXPKTSIZE ; 
 int debug ; 
 struct errmsg* errmsgs ; 
 int errno ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_1__ peer_sock ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int) ; 
 int strerror (int) ; 
 int strlen (int) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int,...) ; 

void
send_error(int peer, int error)
{
	struct tftphdr *tp;
	int length;
	struct errmsg *pe;
	char buf[MAXPKTSIZE];

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG, "Sending ERROR %d", error);

	DROPPACKET("send_error");

	tp = (struct tftphdr *)buf;
	tp->th_opcode = htons((u_short)ERROR);
	tp->th_code = htons((u_short)error);
	for (pe = errmsgs; pe->e_code >= 0; pe++)
		if (pe->e_code == error)
			break;
	if (pe->e_code < 0) {
		pe->e_msg = strerror(error - 100);
		tp->th_code = EUNDEF;   /* set 'undef' errorcode */
	}
	strcpy(tp->th_msg, pe->e_msg);
	length = strlen(pe->e_msg);
	tp->th_msg[length] = '\0';
	length += 5;

	if (debug&DEBUG_PACKETS)
		tftp_log(LOG_DEBUG, "Sending ERROR %d: %s", error, tp->th_msg);

	if (sendto(peer, buf, length, 0,
		(struct sockaddr *)&peer_sock, peer_sock.ss_len) != length)
		tftp_log(LOG_ERR, "send_error: %s", strerror(errno));
}