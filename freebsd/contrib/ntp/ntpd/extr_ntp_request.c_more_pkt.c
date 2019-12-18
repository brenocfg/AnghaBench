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
struct pkt {int dummy; } ;
struct TYPE_3__ {void* data; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  err_nitems; int /*<<< orphan*/  auth_seq; int /*<<< orphan*/  rm_vn_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_SEQ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ MAXSEQ ; 
 int /*<<< orphan*/  MORE_BIT ; 
 int /*<<< orphan*/  RESP_BIT ; 
 scalar_t__ RESP_DATA_SIZE ; 
 scalar_t__ RESP_HEADER_SIZE ; 
 int /*<<< orphan*/  RM_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t databytes ; 
 void* exbuf ; 
 int /*<<< orphan*/  frominter ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ itemsize ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 scalar_t__ nitems ; 
 int /*<<< orphan*/  numresppkts ; 
 int /*<<< orphan*/  reqver ; 
 TYPE_2__ rpkt ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct pkt*,scalar_t__) ; 
 scalar_t__ seqno ; 
 int /*<<< orphan*/  toaddr ; 
 int usingexbuf ; 

__attribute__((used)) static void *
more_pkt(void)
{
	/*
	 * If we were using the extra buffer, send the packet.
	 */
	if (usingexbuf) {
		DPRINTF(3, ("request: sending pkt\n"));
		rpkt.rm_vn_mode = RM_VN_MODE(RESP_BIT, MORE_BIT, reqver);
		rpkt.auth_seq = AUTH_SEQ(0, seqno);
		rpkt.err_nitems = htons((u_short)nitems);
		sendpkt(toaddr, frominter, -1, (struct pkt *)&rpkt,
			RESP_HEADER_SIZE + databytes);
		numresppkts++;

		/*
		 * Copy data out of exbuf into the packet.
		 */
		memcpy(&rpkt.u.data[0], exbuf, (unsigned)itemsize);
		seqno++;
		databytes = 0;
		nitems = 0;
		usingexbuf = 0;
	}

	databytes += itemsize;
	nitems++;
	if (databytes + itemsize <= RESP_DATA_SIZE) {
		DPRINTF(4, ("request: giving him more data\n"));
		/*
		 * More room in packet.  Give him the
		 * next address.
		 */
		return &rpkt.u.data[databytes];
	} else {
		/*
		 * No room in packet.  Give him the extra
		 * buffer unless this was the last in the sequence.
		 */
		DPRINTF(4, ("request: into extra buffer\n"));
		if (seqno == MAXSEQ)
			return NULL;
		else {
			usingexbuf = 1;
			return exbuf;
		}
	}
}