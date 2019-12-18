#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct refclockio {scalar_t__ fd; TYPE_1__* srcclock; struct refclockio* next; } ;
struct asyncio_reader {scalar_t__ fd; int /*<<< orphan*/  (* receiver ) (struct asyncio_reader*) ;struct asyncio_reader* link; } ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_8__ {scalar_t__ fd; int flags; scalar_t__ bfd; struct TYPE_8__* elink; } ;
typedef  TYPE_2__ endpt ;
struct TYPE_9__ {int resp_read_pipe; int /*<<< orphan*/  resp_ready_seen; } ;
typedef  TYPE_3__ blocking_child ;
struct TYPE_7__ {int /*<<< orphan*/  srcadr; } ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 int INT_BCASTOPEN ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  L_SUB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 struct asyncio_reader* asyncio_reader_list ; 
 int /*<<< orphan*/  blocking_child_ready_seen ; 
 TYPE_3__** blocking_children ; 
 size_t blocking_children_alloc ; 
 int /*<<< orphan*/  collect_timing (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int debug ; 
 TYPE_2__* ep_list ; 
 int errno ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_pkts ; 
 char const* lfptoms (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  maintain_activefds (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 
 int read_network_packet (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int read_refclock_packet (scalar_t__,struct refclockio*,int /*<<< orphan*/ ) ; 
 struct refclockio* refio ; 
 char* refnumtoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct asyncio_reader*) ; 

__attribute__((used)) static void
input_handler_scan(
	const l_fp *	cts,
	const fd_set *	pfds
	)
{
	int		buflen;
	u_int		idx;
	int		doing;
	SOCKET		fd;
	blocking_child *c;
	l_fp		ts;	/* Timestamp at BOselect() gob */

#if defined(DEBUG_TIMING)
	l_fp		ts_e;	/* Timestamp at EOselect() gob */
#endif
	endpt *		ep;
#ifdef REFCLOCK
	struct refclockio *rp;
	int		saved_errno;
	const char *	clk;
#endif
#ifdef HAS_ROUTING_SOCKET
	struct asyncio_reader *	asyncio_reader;
	struct asyncio_reader *	next_asyncio_reader;
#endif

	++handler_pkts;
	ts = *cts;

#ifdef REFCLOCK
	/*
	 * Check out the reference clocks first, if any
	 */
	
	for (rp = refio; rp != NULL; rp = rp->next) {
		fd = rp->fd;
		
		if (!FD_ISSET(fd, pfds))
			continue;
		buflen = read_refclock_packet(fd, rp, ts);
		/*
		 * The first read must succeed after select() indicates
		 * readability, or we've reached a permanent EOF.
		 * http://bugs.ntp.org/1732 reported ntpd munching CPU
		 * after a USB GPS was unplugged because select was
		 * indicating EOF but ntpd didn't remove the descriptor
		 * from the activefds set.
		 */
		if (buflen < 0 && EAGAIN != errno) {
			saved_errno = errno;
			clk = refnumtoa(&rp->srcclock->srcadr);
			errno = saved_errno;
			msyslog(LOG_ERR, "%s read: %m", clk);
			maintain_activefds(fd, TRUE);
		} else if (0 == buflen) {
			clk = refnumtoa(&rp->srcclock->srcadr);
			msyslog(LOG_ERR, "%s read EOF", clk);
			maintain_activefds(fd, TRUE);
		} else {
			/* drain any remaining refclock input */
			do {
				buflen = read_refclock_packet(fd, rp, ts);
			} while (buflen > 0);
		}
	}
#endif /* REFCLOCK */

	/*
	 * Loop through the interfaces looking for data to read.
	 */
	for (ep = ep_list; ep != NULL; ep = ep->elink) {
		for (doing = 0; doing < 2; doing++) {
			if (!doing) {
				fd = ep->fd;
			} else {
				if (!(ep->flags & INT_BCASTOPEN))
					break;
				fd = ep->bfd;
			}
			if (fd < 0)
				continue;
			if (FD_ISSET(fd, pfds))
				do {
					buflen = read_network_packet(
							fd, ep, ts);
				} while (buflen > 0);
			/* Check more interfaces */
		}
	}

#ifdef HAS_ROUTING_SOCKET
	/*
	 * scan list of asyncio readers - currently only used for routing sockets
	 */
	asyncio_reader = asyncio_reader_list;

	while (asyncio_reader != NULL) {
		/* callback may unlink and free asyncio_reader */
		next_asyncio_reader = asyncio_reader->link;
		if (FD_ISSET(asyncio_reader->fd, pfds))
			(*asyncio_reader->receiver)(asyncio_reader);
		asyncio_reader = next_asyncio_reader;
	}
#endif /* HAS_ROUTING_SOCKET */

	/*
	 * Check for a response from a blocking child
	 */
	for (idx = 0; idx < blocking_children_alloc; idx++) {
		c = blocking_children[idx];
		if (NULL == c || -1 == c->resp_read_pipe)
			continue;
		if (FD_ISSET(c->resp_read_pipe, pfds)) {
			++c->resp_ready_seen;
			++blocking_child_ready_seen;
		}
	}

	/* We've done our work */
#if defined(DEBUG_TIMING)
	get_systime(&ts_e);
	/*
	 * (ts_e - ts) is the amount of time we spent
	 * processing this gob of file descriptors.  Log
	 * it.
	 */
	L_SUB(&ts_e, &ts);
	collect_timing(NULL, "input handler", 1, &ts_e);
	if (debug > 3)
		msyslog(LOG_DEBUG,
			"input_handler: Processed a gob of fd's in %s msec",
			lfptoms(&ts_e, 6));
#endif /* DEBUG_TIMING */
}