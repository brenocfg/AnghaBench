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
typedef  int uint32_t ;
struct sock_timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {char* data; } ;
struct resp_pkt {int implementation; int request; TYPE_1__ u; int /*<<< orphan*/  rm_vn_mode; int /*<<< orphan*/  auth_seq; int /*<<< orphan*/  mbz_itemsize; int /*<<< orphan*/  err_nitems; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rpkt ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int ERR_INCOMPLETE ; 
 int ERR_TIMEOUT ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int INFO_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ INFO_IS_AUTH (int /*<<< orphan*/ ) ; 
 size_t INFO_ITEMSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ INFO_MBZ (int /*<<< orphan*/ ) ; 
 int INFO_MODE (int /*<<< orphan*/ ) ; 
 size_t INFO_NITEMS (int /*<<< orphan*/ ) ; 
 int INFO_OKAY ; 
 int INFO_SEQ (int /*<<< orphan*/ ) ; 
 int INFO_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ ISMORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISRESPONSE (int /*<<< orphan*/ ) ; 
 int MAXSEQ ; 
 int MODE_PRIVATE ; 
 int NTP_OLDVERSION ; 
 int NTP_VERSION ; 
 int RESP_HEADER_SIZE ; 
 int /*<<< orphan*/  ZERO (char*) ; 
 char* currenthost ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  growpktdata () ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 char* pktdata ; 
 int pktdatasize ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock_timeval*) ; 
 scalar_t__ sockfd ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 struct sock_timeval tvout ; 
 struct sock_timeval tvsout ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  zero_mem (char*,int) ; 

__attribute__((used)) static int
getresponse(
	int implcode,
	int reqcode,
	size_t *ritems,
	size_t *rsize,
	const char **rdata,
	size_t esize
	)
{
	struct resp_pkt rpkt;
	struct sock_timeval tvo;
	size_t items;
	size_t i;
	size_t size;
	size_t datasize;
	char *datap;
	char *tmp_data;
	char haveseq[MAXSEQ+1];
	int firstpkt;
	int lastseq;
	int numrecv;
	int seq;
	fd_set fds;
	ssize_t n;
	int pad;
	/* absolute timeout checks. Not 'time_t' by intention! */
	uint32_t tobase;	/* base value for timeout */
	uint32_t tospan;	/* timeout span (max delay) */
	uint32_t todiff;	/* current delay */

	/*
	 * This is pretty tricky.  We may get between 1 and many packets
	 * back in response to the request.  We peel the data out of
	 * each packet and collect it in one long block.  When the last
	 * packet in the sequence is received we'll know how many we
	 * should have had.  Note we use one long time out, should reconsider.
	 */
	*ritems = 0;
	*rsize = 0;
	firstpkt = 1;
	numrecv = 0;
	*rdata = datap = pktdata;
	lastseq = 999;	/* too big to be a sequence number */
	ZERO(haveseq);
	FD_ZERO(&fds);
	tobase = (uint32_t)time(NULL);

    again:
	if (firstpkt)
		tvo = tvout;
	else
		tvo = tvsout;
	tospan = (uint32_t)tvo.tv_sec + (tvo.tv_usec != 0);
	
	FD_SET(sockfd, &fds);
	n = select(sockfd+1, &fds, NULL, NULL, &tvo);
	if (n == -1) {
		warning("select fails");
		return -1;
	}
	
	/*
	 * Check if this is already too late. Trash the data and fake a
	 * timeout if this is so.
	 */
	todiff = (((uint32_t)time(NULL)) - tobase) & 0x7FFFFFFFu;
	if ((n > 0) && (todiff > tospan)) {
		n = recv(sockfd, (char *)&rpkt, sizeof(rpkt), 0);
		n -= n; /* faked timeout return from 'select()'*/
	}
	
	if (n == 0) {
		/*
		 * Timed out.  Return what we have
		 */
		if (firstpkt) {
			(void) fprintf(stderr,
				       "%s: timed out, nothing received\n",
				       currenthost);
			return ERR_TIMEOUT;
		} else {
			(void) fprintf(stderr,
				       "%s: timed out with incomplete data\n",
				       currenthost);
			if (debug) {
				printf("Received sequence numbers");
				for (n = 0; n <= MAXSEQ; n++)
				    if (haveseq[n])
					printf(" %zd,", (size_t)n);
				if (lastseq != 999)
				    printf(" last frame received\n");
				else
				    printf(" last frame not received\n");
			}
			return ERR_INCOMPLETE;
		}
	}

	n = recv(sockfd, (char *)&rpkt, sizeof(rpkt), 0);
	if (n == -1) {
		warning("read");
		return -1;
	}


	/*
	 * Check for format errors.  Bug proofing.
	 */
	if (n < (ssize_t)RESP_HEADER_SIZE) {
		if (debug)
			printf("Short (%zd byte) packet received\n", (size_t)n);
		goto again;
	}
	if (INFO_VERSION(rpkt.rm_vn_mode) > NTP_VERSION ||
	    INFO_VERSION(rpkt.rm_vn_mode) < NTP_OLDVERSION) {
		if (debug)
			printf("Packet received with version %d\n",
			       INFO_VERSION(rpkt.rm_vn_mode));
		goto again;
	}
	if (INFO_MODE(rpkt.rm_vn_mode) != MODE_PRIVATE) {
		if (debug)
			printf("Packet received with mode %d\n",
			       INFO_MODE(rpkt.rm_vn_mode));
		goto again;
	}
	if (INFO_IS_AUTH(rpkt.auth_seq)) {
		if (debug)
			printf("Encrypted packet received\n");
		goto again;
	}
	if (!ISRESPONSE(rpkt.rm_vn_mode)) {
		if (debug)
			printf("Received request packet, wanted response\n");
		goto again;
	}
	if (INFO_MBZ(rpkt.mbz_itemsize) != 0) {
		if (debug)
			printf("Received packet with nonzero MBZ field!\n");
		goto again;
	}

	/*
	 * Check implementation/request.  Could be old data getting to us.
	 */
	if (rpkt.implementation != implcode || rpkt.request != reqcode) {
		if (debug)
			printf(
			    "Received implementation/request of %d/%d, wanted %d/%d",
			    rpkt.implementation, rpkt.request,
			    implcode, reqcode);
		goto again;
	}

	/*
	 * Check the error code.  If non-zero, return it.
	 */
	if (INFO_ERR(rpkt.err_nitems) != INFO_OKAY) {
		if (debug && ISMORE(rpkt.rm_vn_mode)) {
			printf("Error code %d received on not-final packet\n",
			       INFO_ERR(rpkt.err_nitems));
		}
		return (int)INFO_ERR(rpkt.err_nitems);
	}

	/*
	 * Collect items and size.  Make sure they make sense.
	 */
	items = INFO_NITEMS(rpkt.err_nitems);
	size = INFO_ITEMSIZE(rpkt.mbz_itemsize);
	if (esize > size)
		pad = esize - size;
	else 
		pad = 0;
	datasize = items * size;
	if ((size_t)datasize > (n-RESP_HEADER_SIZE)) {
		if (debug)
		    printf(
			    "Received items %zu, size %zu (total %zu), data in packet is %zu\n",
			    items, size, datasize, n-RESP_HEADER_SIZE);
		goto again;
	}

	/*
	 * If this isn't our first packet, make sure the size matches
	 * the other ones.
	 */
	if (!firstpkt && size != *rsize) {
		if (debug)
		    printf("Received itemsize %zu, previous %zu\n",
			   size, *rsize);
		goto again;
	}
	/*
	 * If we've received this before, +toss it
	 */
	seq = INFO_SEQ(rpkt.auth_seq);
	if (haveseq[seq]) {
		if (debug)
		    printf("Received duplicate sequence number %d\n", seq);
		goto again;
	}
	haveseq[seq] = 1;

	/*
	 * If this is the last in the sequence, record that.
	 */
	if (!ISMORE(rpkt.rm_vn_mode)) {
		if (lastseq != 999) {
			printf("Received second end sequence packet\n");
			goto again;
		}
		lastseq = seq;
	}

	/*
	 * So far, so good.  Copy this data into the output array. Bump
	 * the timeout base, in case we expect more data.
	 */
	tobase = (uint32_t)time(NULL);
	if ((datap + datasize + (pad * items)) > (pktdata + pktdatasize)) {
		size_t offset = datap - pktdata;
		growpktdata();
		*rdata = pktdata; /* might have been realloced ! */
		datap = pktdata + offset;
	}
	/* 
	 * We now move the pointer along according to size and number of
	 * items.  This is so we can play nice with older implementations
	 */

	tmp_data = rpkt.u.data;
	for (i = 0; i < items; i++) {
		memcpy(datap, tmp_data, (unsigned)size);
		tmp_data += size;
		zero_mem(datap + size, pad);
		datap += size + pad;
	}

	if (firstpkt) {
		firstpkt = 0;
		*rsize = size + pad;
	}
	*ritems += items;

	/*
	 * Finally, check the count of received packets.  If we've got them
	 * all, return
	 */
	++numrecv;
	if (numrecv <= lastseq)
		goto again;
	return INFO_OKAY;
}