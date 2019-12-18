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
struct req_pkt {int /*<<< orphan*/  request; int /*<<< orphan*/  implementation; } ;
struct pkt {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  endpt ;
struct TYPE_2__ {int /*<<< orphan*/  mbz_itemsize; int /*<<< orphan*/  err_nitems; int /*<<< orphan*/  request; int /*<<< orphan*/  implementation; int /*<<< orphan*/  auth_seq; int /*<<< orphan*/  rm_vn_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_SEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NITEMS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBZ_ITEMSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESP_BIT ; 
 int /*<<< orphan*/  RESP_HEADER_SIZE ; 
 int /*<<< orphan*/  RM_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * errorcounter ; 
 int /*<<< orphan*/  reqver ; 
 TYPE_1__ rpkt ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct pkt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
req_ack(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt,
	int errcode
	)
{
	/*
	 * fill in the fields
	 */
	rpkt.rm_vn_mode = RM_VN_MODE(RESP_BIT, 0, reqver);
	rpkt.auth_seq = AUTH_SEQ(0, 0);
	rpkt.implementation = inpkt->implementation;
	rpkt.request = inpkt->request;
	rpkt.err_nitems = ERR_NITEMS(errcode, 0); 
	rpkt.mbz_itemsize = MBZ_ITEMSIZE(0);

	/*
	 * send packet and bump counters
	 */
	sendpkt(srcadr, inter, -1, (struct pkt *)&rpkt, RESP_HEADER_SIZE);
	errorcounter[errcode]++;
}