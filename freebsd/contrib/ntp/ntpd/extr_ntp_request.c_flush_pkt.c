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
struct req_pkt {int dummy; } ;
struct pkt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  err_nitems; int /*<<< orphan*/  auth_seq; int /*<<< orphan*/  rm_vn_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_SEQ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  INFO_ERR_NODATA ; 
 int /*<<< orphan*/  RESP_BIT ; 
 scalar_t__ RESP_HEADER_SIZE ; 
 int /*<<< orphan*/  RM_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ databytes ; 
 int /*<<< orphan*/  frominter ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nitems ; 
 int /*<<< orphan*/  numresppkts ; 
 int /*<<< orphan*/  req_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct req_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reqver ; 
 TYPE_1__ rpkt ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct pkt*,scalar_t__) ; 
 scalar_t__ seqno ; 
 int /*<<< orphan*/  toaddr ; 

__attribute__((used)) static void
flush_pkt(void)
{
	DPRINTF(3, ("request: flushing packet, %d items\n", nitems));
	/*
	 * Must send the last packet.  If nothing in here and nothing
	 * has been sent, send an error saying no data to be found.
	 */
	if (seqno == 0 && nitems == 0)
		req_ack(toaddr, frominter, (struct req_pkt *)&rpkt,
			INFO_ERR_NODATA);
	else {
		rpkt.rm_vn_mode = RM_VN_MODE(RESP_BIT, 0, reqver);
		rpkt.auth_seq = AUTH_SEQ(0, seqno);
		rpkt.err_nitems = htons((u_short)nitems);
		sendpkt(toaddr, frominter, -1, (struct pkt *)&rpkt,
			RESP_HEADER_SIZE+databytes);
		numresppkts++;
	}
}