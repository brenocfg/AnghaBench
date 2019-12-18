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
struct sock_timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
#define  ERR_INCOMPLETE 135 
#define  ERR_TIMEOUT 134 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ IMPL_XNTPD ; 
#define  INFO_ERR_AUTH 133 
#define  INFO_ERR_FMT 132 
#define  INFO_ERR_IMPL 131 
#define  INFO_ERR_NODATA 130 
#define  INFO_ERR_REQ 129 
#define  REQ_LEN_NOMAC 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getresponse (int,int,size_t*,size_t*,char const**,int) ; 
 int /*<<< orphan*/  havehost ; 
 scalar_t__ impl_ver ; 
 int /*<<< orphan*/  recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int req_pkt_size ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock_timeval*) ; 
 int sendrequest (int,int,int,size_t,size_t,char const*) ; 
 scalar_t__ sockfd ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warning (char*) ; 

int
doquery(
	int implcode,
	int reqcode,
	int auth,
	size_t qitems,
	size_t qsize,
	const char *qdata,
	size_t *ritems,
	size_t *rsize,
	const char **rdata,
 	int quiet_mask,
	int esize
	)
{
	int res;
	char junk[512];
	fd_set fds;
	struct sock_timeval tvzero;

	/*
	 * Check to make sure host is open
	 */
	if (!havehost) {
		(void) fprintf(stderr, "***No host open, use `host' command\n");
		return -1;
	}

	/*
	 * Poll the socket and clear out any pending data
	 */
again:
	do {
		tvzero.tv_sec = tvzero.tv_usec = 0;
		FD_ZERO(&fds);
		FD_SET(sockfd, &fds);
		res = select(sockfd+1, &fds, NULL, NULL, &tvzero);
		if (res == -1) {
			warning("polling select");
			return -1;
		} else if (res > 0)

		    (void) recv(sockfd, junk, sizeof junk, 0);
	} while (res > 0);


	/*
	 * send a request
	 */
	res = sendrequest(implcode, reqcode, auth, qitems, qsize, qdata);
	if (res != 0)
		return res;
	
	/*
	 * Get the response.  If we got a standard error, print a message
	 */
	res = getresponse(implcode, reqcode, ritems, rsize, rdata, esize);

	/*
	 * Try to be compatible with older implementations of ntpd.
	 */
	if (res == INFO_ERR_FMT && req_pkt_size != 48) {
		int oldsize;

		oldsize = req_pkt_size;

		switch(req_pkt_size) {
		case REQ_LEN_NOMAC:
			req_pkt_size = 160;
			break;
		case 160:
			req_pkt_size = 48;
			break;
		}
		if (impl_ver == IMPL_XNTPD) {
			fprintf(stderr,
			    "***Warning changing to older implementation\n");
			return INFO_ERR_IMPL;
		}

		fprintf(stderr,
		    "***Warning changing the request packet size from %d to %d\n",
		    oldsize, req_pkt_size);
		goto again;
	}

 	/* log error message if not told to be quiet */
 	if ((res > 0) && (((1 << res) & quiet_mask) == 0)) {
		switch(res) {
		case INFO_ERR_IMPL:
			/* Give us a chance to try the older implementation. */
			if (implcode == IMPL_XNTPD)
				break;
			(void) fprintf(stderr,
				       "***Server implementation incompatible with our own\n");
			break;
		case INFO_ERR_REQ:
			(void) fprintf(stderr,
				       "***Server doesn't implement this request\n");
			break;
		case INFO_ERR_FMT:
			(void) fprintf(stderr,
				       "***Server reports a format error in the received packet (shouldn't happen)\n");
			break;
		case INFO_ERR_NODATA:
			(void) fprintf(stderr,
				       "***Server reports data not found\n");
			break;
		case INFO_ERR_AUTH:
			(void) fprintf(stderr, "***Permission denied\n");
			break;
		case ERR_TIMEOUT:
			(void) fprintf(stderr, "***Request timed out\n");
			break;
		case ERR_INCOMPLETE:
			(void) fprintf(stderr,
				       "***Response from server was incomplete\n");
			break;
		default:
			(void) fprintf(stderr,
				       "***Server returns unknown error code %d\n", res);
			break;
		}
	}
	return res;
}