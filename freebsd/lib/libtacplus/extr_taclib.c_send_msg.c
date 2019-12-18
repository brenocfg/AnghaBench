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
struct timeval {scalar_t__ tv_sec; } ;
struct tac_msg {int seq_no; int /*<<< orphan*/  length; int /*<<< orphan*/  flags; } ;
struct tac_handle {int last_seq_no; size_t cur_server; scalar_t__ fd; TYPE_1__* servers; scalar_t__ single_connect; struct tac_msg request; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {scalar_t__ timeout; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int HDRSIZE ; 
 int /*<<< orphan*/  TAC_SINGLE_CONNECT ; 
 int /*<<< orphan*/  crypt_msg (struct tac_handle*,struct tac_msg*) ; 
 scalar_t__ errno ; 
 int establish_connection (struct tac_handle*) ; 
 int /*<<< orphan*/  gen_session_id (struct tac_msg*) ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*,...) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int write (scalar_t__,char*,int) ; 

__attribute__((used)) static int
send_msg(struct tac_handle *h)
{
	struct timeval deadline;
	struct tac_msg *msg;
	char *ptr;
	int len;

	if (h->last_seq_no & 1) {
		generr(h, "Attempt to send message out of sequence");
		return -1;
	}

	if (establish_connection(h) == -1)
		return -1;

	msg = &h->request;
	msg->seq_no = ++h->last_seq_no;
	if (msg->seq_no == 1)
		gen_session_id(msg);
	crypt_msg(h, msg);

	if (h->single_connect)
		msg->flags |= TAC_SINGLE_CONNECT;
	else
		msg->flags &= ~TAC_SINGLE_CONNECT;
	gettimeofday(&deadline, NULL);
	deadline.tv_sec += h->servers[h->cur_server].timeout;
	len = HDRSIZE + ntohl(msg->length);
	ptr = (char *)msg;
	while (len > 0) {
		int n;

		n = write(h->fd, ptr, len);
		if (n == -1) {
			struct timeval tv;
			int nfds;

			if (errno != EAGAIN) {
				generr(h, "Network write error: %s",
				    strerror(errno));
				return -1;
			}

			/* Wait until we can write more data. */
			gettimeofday(&tv, NULL);
			timersub(&deadline, &tv, &tv);
			if (tv.tv_sec >= 0) {
				fd_set wfds;

				FD_ZERO(&wfds);
				FD_SET(h->fd, &wfds);
				nfds =
				    select(h->fd + 1, NULL, &wfds, NULL, &tv);
				if (nfds == -1) {
					generr(h, "select: %s",
					    strerror(errno));
					return -1;
				}
			} else
				nfds = 0;
			if (nfds == 0) {
				generr(h, "Network write timed out");
				return -1;
			}
		} else {
			ptr += n;
			len -= n;
		}
	}
	return 0;
}