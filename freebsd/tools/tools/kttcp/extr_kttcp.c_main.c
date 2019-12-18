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
typedef  scalar_t__ u_long ;
struct timeval {unsigned long long tv_sec; unsigned long long tv_usec; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_len; } ;
struct sockaddr {int dummy; } ;
struct rusage {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
struct TYPE_2__ {unsigned long long tv_usec; scalar_t__ tv_sec; } ;
struct kttcp_io_args {int kio_socket; unsigned long long kio_totalsize; long long kio_bytesdone; TYPE_1__ kio_elapsed; } ;
struct addrinfo {int ai_flags; int ai_family; int /*<<< orphan*/  ai_addrlen; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int AI_PASSIVE ; 
 unsigned long long INT_MAX ; 
 int /*<<< orphan*/  KTTCP_DEVICE ; 
 scalar_t__ KTTCP_IO_RECV ; 
 scalar_t__ KTTCP_IO_SEND ; 
 unsigned long long KTTCP_MAX_XMIT ; 
 char* KTTCP_PORT ; 
 int KTTCP_SOCKBUF_DEFAULT ; 
 unsigned long long KTTCP_XMITSIZE ; 
 unsigned long long NBBY ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int PF_UNSPEC ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 unsigned long long get_bytes (char*) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int ioctl (int,scalar_t__,struct kttcp_io_args*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int c, error, s, verbose, s2, kfd;
	int xmitset, family;
	int bufsize;
	int ai_flag;
	char *host;
	char *portstr;
	struct kttcp_io_args kio;
	struct addrinfo hints, *addr, *res;
	struct sockaddr_storage ss;
	struct rusage rustart, ruend;
	struct timeval tvtmp;
	unsigned long long ull, usecs, bytespersec, bitspersec, xmitsize;
	char connecthost[NI_MAXHOST];
	socklen_t slen;
	const int one = 1;
	u_long cmd;

	cmd = 0;
	portstr = KTTCP_PORT;
	verbose = 1;
	xmitset = 0;
	bufsize = KTTCP_SOCKBUF_DEFAULT;
	xmitsize = KTTCP_XMITSIZE;
	family = PF_UNSPEC;
	while ((c = getopt(argc, argv, "46b:n:p:qrtvw:")) != -1) {
		switch (c) {
		case '4':
			if (family != PF_UNSPEC)
				usage();
			family = PF_INET;
			break;
		case '6':
			if (family != PF_UNSPEC)
				usage();
			family = PF_INET6;
			break;
		case 'b':
			ull = get_bytes(optarg);
			if (ull > INT_MAX)
				errx(1,
				    "invalid socket buffer size: %s\n", optarg);
			bufsize = ull;
			break;
		case 'n':
			xmitsize = get_bytes(optarg);
			xmitset = 1;
			break;
		case 'p':
			portstr = optarg;
			break;
		case 'q':
			verbose = 0;
			break;
		case 'r':
			if (cmd != 0)
				usage();
			cmd = KTTCP_IO_RECV;
			break;
		case 't':
			if (cmd != 0)
				usage();
			cmd = KTTCP_IO_SEND;
			break;
		case 'v':
			verbose = 2;
			break;
		case '?':
		default:
			usage();
		}
	}
	if (cmd == 0)
		usage();

	argc -= optind;
	argv += optind;

	if (cmd == KTTCP_IO_SEND) {
		if (xmitsize <= 0 || argc < 1)
			usage();
		host = argv[0];
		ai_flag = 0;
	} else {
		if (xmitset == 0)
			xmitsize = KTTCP_MAX_XMIT;
		host = NULL;
		ai_flag = AI_PASSIVE;
	}

	if ((kfd = open(KTTCP_DEVICE, O_RDWR, 666)) == -1)
		err(2, "open %s", KTTCP_DEVICE);

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = ai_flag;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = family;
	error = getaddrinfo(host, portstr, &hints, &addr);

	if (error != 0)
		errx(2, "%s", gai_strerror(error));

	s = -1;
	for (res = addr; res != NULL; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (s >= 0)
			break;
	}
	if (res == NULL)
		err(2, "can't create socket");

	printf("kttcp: socket buffer size: %d\n", bufsize);

	if (cmd == KTTCP_IO_SEND) {
		if (connect(s, res->ai_addr, res->ai_addrlen) < 0)
			err(2, "connect");
		if (verbose) {
			getnameinfo(res->ai_addr, res->ai_addrlen,
			    connecthost, sizeof connecthost, NULL, 0,
			    NI_NUMERICHOST);
			printf("kttcp: connected to %s\n", connecthost);
		}
		if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof (int))
		    < 0)
			err(2, "setsockopt sndbuf");
		kio.kio_socket = s;
	} else {
		if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one,
		    sizeof (int)) < 0)
			err(2, "setsockopt reuseaddr");
		if (bind(s, res->ai_addr, res->ai_addrlen) < 0)
			err(2, "bind");
		if (listen(s, 1) < 0)
			err(2, "listen");
		if (verbose)
			printf("kttcp: listening on port %s\n", portstr);
		slen = sizeof ss;
		s2 = accept(s, (struct sockaddr *)&ss, &slen);
		if (s2 < 0)
			err(2, "accept");
		if (verbose) {
			getnameinfo((struct sockaddr *)&ss, ss.ss_len,
			    connecthost, sizeof connecthost, NULL, 0,
			    NI_NUMERICHOST);
			printf("kttcp: connect from %s\n", connecthost);
		}
		if (setsockopt(s2, SOL_SOCKET, SO_RCVBUF, &bufsize,
		    sizeof (int)) < 0)
			err(2, "setsockopt rcvbuf");
		kio.kio_socket = s2;
	}

	kio.kio_totalsize = xmitsize;

	getrusage(RUSAGE_SELF, &rustart);
	if (ioctl(kfd, cmd, &kio) == -1)
		err(2, "kttcp i/o command");
	getrusage(RUSAGE_SELF, &ruend);

	usecs = (unsigned long long)kio.kio_elapsed.tv_sec * 1000000;
	usecs += kio.kio_elapsed.tv_usec;

	bytespersec = kio.kio_bytesdone * 1000000LL / usecs;
	bitspersec = bytespersec * NBBY;
	printf("kttcp: %llu bytes in %ld.%03ld real seconds ==> %llu bytes/sec\n",
	    kio.kio_bytesdone, kio.kio_elapsed.tv_sec,
	    kio.kio_elapsed.tv_usec / 1000, bytespersec);
	if (verbose > 1) {
		timersub(&ruend.ru_stime, &rustart.ru_stime, &tvtmp);
		bytespersec = kio.kio_bytesdone * 1000000LL /
		    (tvtmp.tv_sec * 1000000ULL + tvtmp.tv_usec);
		printf("kttcp: %llu bytes in %ld.%03ld CPU seconds ==> %llu bytes/CPU sec\n",
		    kio.kio_bytesdone, tvtmp.tv_sec, tvtmp.tv_usec / 1000, bytespersec);
	}
	printf("       %g (%g) Megabits/sec\n",
	    ((double) bitspersec / 1024.0) / 1024.0,
	    ((double) bitspersec / 1000.0) / 1000.0);

	timersub(&ruend.ru_utime, &rustart.ru_utime, &tvtmp);
	/* XXX
	 * sometimes, this ends up as -1 * hz!?
	 */
	if (tvtmp.tv_sec < 0)
		tvtmp.tv_sec = tvtmp.tv_usec = 0;
	printf("  %ld.%02lduser", tvtmp.tv_sec, tvtmp.tv_usec / 10000);
	ull = tvtmp.tv_sec * 1000000ULL + tvtmp.tv_usec;

	timersub(&ruend.ru_stime, &rustart.ru_stime, &tvtmp);
	printf(" %ld.%02ldsys", tvtmp.tv_sec, tvtmp.tv_usec / 10000);
	ull += tvtmp.tv_sec * 1000000ULL + tvtmp.tv_usec;

	printf(" %lld.%lldreal", usecs / 1000000, (usecs % 1000000) / 10000);
	printf(" %lld%%", ull * 100 / usecs);
	printf("\n");


	close(kio.kio_socket);
	if (cmd == KTTCP_IO_RECV)
		close(s);
	close(kfd);
	freeaddrinfo(addr);

	return 0;
}