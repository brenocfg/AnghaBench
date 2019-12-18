#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  thetime ;
struct timeval {int tv_sec; int member_0; scalar_t__ tv_usec; int /*<<< orphan*/  member_1; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_9__ {int ep_len; TYPE_3__* ep_val; } ;
struct TYPE_10__ {TYPE_1__ ep; } ;
typedef  TYPE_2__ nis_server ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_11__ {char* uaddr; int /*<<< orphan*/  proto; } ;
typedef  TYPE_3__ endpoint ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPCBPROC_GETTIME ; 
 int /*<<< orphan*/  RPCBPROG ; 
 int /*<<< orphan*/  RPCBVERS ; 
 int RPC_ANYSOCK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  SIGALRM ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int TOFFSET ; 
 int /*<<< orphan*/  _close (int) ; 
 int _connect (int,struct sockaddr*,int) ; 
 int _read (int,char*,int) ; 
 int _recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  _rpc_dtablesize () ; 
 int _select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int _sendto (int,int*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm (int) ; 
 void alarm_hndler (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct timeval) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free_eps (TYPE_3__*,int) ; 
 TYPE_2__* get_server (struct sockaddr_in*,char*,TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (char*) ; 
 int ntohl (int) ; 
 scalar_t__ saw_alarm ; 
 scalar_t__ signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*,int*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ uaddr_to_sockaddr (char*,struct sockaddr_in*) ; 
 scalar_t__ xdr_u_long ; 
 scalar_t__ xdr_void ; 

int
__rpc_get_time_offset(struct timeval *td, nis_server *srv, char *thost,
    char **uaddr, struct sockaddr_in *netid)
{
	CLIENT			*clnt; 		/* Client handle 	*/
	endpoint		*ep,		/* useful endpoints	*/
				*useep = NULL;	/* endpoint of xp	*/
	char			*useua = NULL;	/* uaddr of selected xp	*/
	int			epl, i;		/* counters		*/
	enum clnt_stat		status;		/* result of clnt_call	*/
	u_long			thetime, delta;
	int			needfree = 0;
	struct timeval		tv;
	int			time_valid;
	int			udp_ep = -1, tcp_ep = -1;
	int			a1, a2, a3, a4;
	char			ut[64], ipuaddr[64];
	endpoint		teps[32];
	nis_server		tsrv;
	void			(*oldsig)(int) = NULL; /* old alarm handler */
	struct sockaddr_in	sin;
	socklen_t		len;
	int			s = RPC_ANYSOCK;
	int			type = 0;

	td->tv_sec = 0;
	td->tv_usec = 0;

	/*
	 * First check to see if we need to find and address for this
	 * server.
	 */
	if (*uaddr == NULL) {
		if ((srv != NULL) && (thost != NULL)) {
			msg("both timehost and srv pointer used!");
			return (0);
		}
		if (! srv) {
			srv = get_server(netid, thost, &tsrv, teps, 32);
			if (srv == NULL) {
				msg("unable to contruct server data.");
				return (0);
			}
			needfree = 1;	/* need to free data in endpoints */
		}

		ep = srv->ep.ep_val;
		epl = srv->ep.ep_len;

		/* Identify the TCP and UDP endpoints */
		for (i = 0;
			(i < epl) && ((udp_ep == -1) || (tcp_ep == -1)); i++) {
			if (strcasecmp(ep[i].proto, "udp") == 0)
				udp_ep = i;
			if (strcasecmp(ep[i].proto, "tcp") == 0)
				tcp_ep = i;
		}

		/* Check to see if it is UDP or TCP */
		if (tcp_ep > -1) {
			useep = &ep[tcp_ep];
			useua = ep[tcp_ep].uaddr;
			type = SOCK_STREAM;
		} else if (udp_ep > -1) {
			useep = &ep[udp_ep];
			useua = ep[udp_ep].uaddr;
			type = SOCK_DGRAM;
		}

		if (useep == NULL) {
			msg("no acceptable transport endpoints.");
			if (needfree)
				free_eps(teps, tsrv.ep.ep_len);
			return (0);
		}
	}

	/*
	 * Create a sockaddr from the uaddr.
	 */
	if (*uaddr != NULL)
		useua = *uaddr;

	/* Fixup test for NIS+ */
	sscanf(useua, "%d.%d.%d.%d.", &a1, &a2, &a3, &a4);
	sprintf(ipuaddr, "%d.%d.%d.%d.0.111", a1, a2, a3, a4);
	useua = &ipuaddr[0];

	bzero((char *)&sin, sizeof(sin));
	if (uaddr_to_sockaddr(useua, &sin)) {
		msg("unable to translate uaddr to sockaddr.");
		if (needfree)
			free_eps(teps, tsrv.ep.ep_len);
		return (0);
	}

	/*
	 * Create the client handle to rpcbind. Note we always try
	 * version 3 since that is the earliest version that supports
	 * the RPCB_GETTIME call. Also it is the version that comes
	 * standard with SVR4. Since most everyone supports TCP/IP
	 * we could consider trying the rtime call first.
	 */
	clnt = clnttcp_create(&sin, RPCBPROG, RPCBVERS, &s, 0, 0);
	if (clnt == NULL) {
		msg("unable to create client handle to rpcbind.");
		if (needfree)
			free_eps(teps, tsrv.ep.ep_len);
		return (0);
	}

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	time_valid = 0;
	status = clnt_call(clnt, RPCBPROC_GETTIME, (xdrproc_t)xdr_void, NULL,
					(xdrproc_t)xdr_u_long, &thetime, tv);
	/*
	 * The only error we check for is anything but success. In
	 * fact we could have seen PROGMISMATCH if talking to a 4.1
	 * machine (pmap v2) or TIMEDOUT if the net was busy.
	 */
	if (status == RPC_SUCCESS)
		time_valid = 1;
	else {
		int save;

		/* Blow away possible stale CLNT handle. */
		if (clnt != NULL) {
			clnt_destroy(clnt);
			clnt = NULL;
		}

		/*
		 * Convert PMAP address into timeservice address
		 * We take advantage of the fact that we "know" what
		 * the universal address looks like for inet transports.
		 *
		 * We also know that the internet timeservice is always
		 * listening on port 37.
		 */
		sscanf(useua, "%d.%d.%d.%d.", &a1, &a2, &a3, &a4);
		sprintf(ut, "%d.%d.%d.%d.0.37", a1, a2, a3, a4);

		if (uaddr_to_sockaddr(ut, &sin)) {
			msg("cannot convert timeservice uaddr to sockaddr.");
			goto error;
		}

		s = _socket(AF_INET, type, 0);
		if (s == -1) {
			msg("unable to open fd to network.");
			goto error;
		}

		/*
		 * Now depending on whether or not we're talking to
		 * UDP we set a timeout or not.
		 */
		if (type == SOCK_DGRAM) {
			struct timeval timeout = { 20, 0 };
			struct sockaddr_in from;
			fd_set readfds;
			int res;

			if (_sendto(s, &thetime, sizeof(thetime), 0,
				(struct sockaddr *)&sin, sizeof(sin)) == -1) {
				msg("udp : sendto failed.");
				goto error;
			}
			do {
				FD_ZERO(&readfds);
				FD_SET(s, &readfds);
				res = _select(_rpc_dtablesize(), &readfds,
				     (fd_set *)NULL, (fd_set *)NULL, &timeout);
			} while (res < 0 && errno == EINTR);
			if (res <= 0)
				goto error;
			len = sizeof(from);
			res = _recvfrom(s, (char *)&thetime, sizeof(thetime), 0,
				       (struct sockaddr *)&from, &len);
			if (res == -1) {
				msg("recvfrom failed on udp transport.");
				goto error;
			}
			time_valid = 1;
		} else {
			int res;

			oldsig = (void (*)(int))signal(SIGALRM, alarm_hndler);
			saw_alarm = 0; /* global tracking the alarm */
			alarm(20); /* only wait 20 seconds */
			res = _connect(s, (struct sockaddr *)&sin, sizeof(sin));
			if (res == -1) {
				msg("failed to connect to tcp endpoint.");
				goto error;
			}
			if (saw_alarm) {
				msg("alarm caught it, must be unreachable.");
				goto error;
			}
			res = _read(s, (char *)&thetime, sizeof(thetime));
			if (res != sizeof(thetime)) {
				if (saw_alarm)
					msg("timed out TCP call.");
				else
					msg("wrong size of results returned");

				goto error;
			}
			time_valid = 1;
		}
		save = errno;
		(void)_close(s);
		errno = save;
		s = RPC_ANYSOCK;

		if (time_valid) {
			thetime = ntohl(thetime);
			thetime = thetime - TOFFSET; /* adjust to UNIX time */
		} else
			thetime = 0;
	}

	gettimeofday(&tv, 0);

error:
	/*
	 * clean up our allocated data structures.
	 */

	if (s != RPC_ANYSOCK)
		(void)_close(s);

	if (clnt != NULL)
		clnt_destroy(clnt);

	alarm(0);	/* reset that alarm if its outstanding */
	if (oldsig) {
		signal(SIGALRM, oldsig);
	}

	/*
	 * note, don't free uaddr strings until after we've made a
	 * copy of them.
	 */
	if (time_valid) {
		if (*uaddr == NULL)
			*uaddr = strdup(useua);

		/* Round to the nearest second */
		tv.tv_sec += (tv.tv_sec > 500000) ? 1 : 0;
		delta = (thetime > tv.tv_sec) ? thetime - tv.tv_sec :
						tv.tv_sec - thetime;
		td->tv_sec = (thetime < tv.tv_sec) ? - delta : delta;
		td->tv_usec = 0;
	} else {
		msg("unable to get the server's time.");
	}

	if (needfree)
		free_eps(teps, tsrv.ep.ep_len);

	return (time_valid);
}