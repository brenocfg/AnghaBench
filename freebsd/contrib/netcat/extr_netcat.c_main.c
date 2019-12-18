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
typedef  int /*<<< orphan*/  z ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct servent {char* s_name; } ;
struct option {char* member_0; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct addrinfo {int /*<<< orphan*/  ai_flags; void* ai_protocol; void* ai_socktype; scalar_t__ ai_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  cliaddr ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int Dflag ; 
 int Fflag ; 
 int /*<<< orphan*/  FreeBSD_Oflag ; 
 int INT_MAX ; 
 void* IPPROTO_TCP ; 
 void* IPPROTO_UDP ; 
 void* Iflag ; 
 int /*<<< orphan*/  MSG_PEEK ; 
 int Nflag ; 
 void* Oflag ; 
 char* Pflag ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 void* SOCK_DGRAM ; 
 void* SOCK_STREAM ; 
 int Sflag ; 
 int Tflag ; 
 int UINT_MAX ; 
 int UNIX_DG_TMP_SOCKET_SIZE ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  build_ports (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int dflag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ family ; 
 int /*<<< orphan*/  fdpass (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  help () ; 
 void* iflag ; 
 char** ipsec_policy ; 
 int kflag ; 
 int lflag ; 
 int local_listen (char*,char*,struct addrinfo) ; 
 int /*<<< orphan*/  map_tos (char*,int*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mktemp (char*) ; 
 int nflag ; 
 int /*<<< orphan*/  no_argument ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 char* pflag ; 
 char** portlist ; 
 int /*<<< orphan*/  readwrite (int) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int remote_connect (char*,char*,struct addrinfo) ; 
 int /*<<< orphan*/  report_connect (struct sockaddr*,int) ; 
 int rflag ; 
 int rtableid ; 
 char* sflag ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socks_connect (char*,char*,struct addrinfo,char const*,char const*,struct addrinfo,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* strtonum (char*,int,int,char const**) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tflag ; 
 int timeout ; 
 int udptest (int) ; 
 int uflag ; 
 int unix_bind (char*) ; 
 int unix_connect (char*) ; 
 char* unix_dg_tmp_socket ; 
 int unix_listen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int vflag ; 
 int xflag ; 
 int zflag ; 

int
main(int argc, char *argv[])
{
	int ch, s, ret, socksv, ipsec_count;
	int numfibs;
	size_t intsize = sizeof(int);
	char *host, *uport;
	struct addrinfo hints;
	struct servent *sv;
	socklen_t len;
	struct sockaddr_storage cliaddr;
	char *proxy;
	const char *errstr, *proxyhost = "", *proxyport = NULL;
	struct addrinfo proxyhints;
	char unix_dg_tmp_socket_buf[UNIX_DG_TMP_SOCKET_SIZE];
	struct option longopts[] = {
		{ "no-tcpopt",	no_argument,	&FreeBSD_Oflag,	1 },
		{ NULL,		0,		NULL,		0 }
	};

	ret = 1;
	ipsec_count = 0;
	s = 0;
	socksv = 5;
	host = NULL;
	uport = NULL;
	sv = NULL;

	signal(SIGPIPE, SIG_IGN);

	while ((ch = getopt_long(argc, argv,
	    "46DdEe:FhI:i:klNnoO:P:p:rSs:tT:UuV:vw:X:x:z",
	    longopts, NULL)) != -1) {
		switch (ch) {
		case '4':
			family = AF_INET;
			break;
		case '6':
			family = AF_INET6;
			break;
		case 'U':
			family = AF_UNIX;
			break;
		case 'X':
			if (strcasecmp(optarg, "connect") == 0)
				socksv = -1; /* HTTP proxy CONNECT */
			else if (strcmp(optarg, "4") == 0)
				socksv = 4; /* SOCKS v.4 */
			else if (strcmp(optarg, "5") == 0)
				socksv = 5; /* SOCKS v.5 */
			else
				errx(1, "unsupported proxy protocol");
			break;
		case 'd':
			dflag = 1;
			break;
		case 'e':
#ifdef IPSEC
			ipsec_policy[ipsec_count++ % 2] = optarg;
#else
			errx(1, "IPsec support unavailable.");
#endif
			break;
		case 'E':
#ifdef IPSEC
			ipsec_policy[0] = "in  ipsec esp/transport//require";
			ipsec_policy[1] = "out ipsec esp/transport//require";
#else
			errx(1, "IPsec support unavailable.");
#endif
			break;
		case 'F':
			Fflag = 1;
			break;
		case 'h':
			help();
			break;
		case 'i':
			iflag = strtonum(optarg, 0, UINT_MAX, &errstr);
			if (errstr)
				errx(1, "interval %s: %s", errstr, optarg);
			break;
		case 'k':
			kflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'N':
			Nflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		case 'o':
			fprintf(stderr, "option -o is deprecated.\n");
			break;
		case 'P':
			Pflag = optarg;
			break;
		case 'p':
			pflag = optarg;
			break;
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = optarg;
			break;
		case 't':
			tflag = 1;
			break;
		case 'u':
			uflag = 1;
			break;
		case 'V':
			if (sysctlbyname("net.fibs", &numfibs, &intsize, NULL, 0) == -1)
				errx(1, "Multiple FIBS not supported");
			rtableid = (int)strtonum(optarg, 0,
			    numfibs - 1, &errstr);
			if (errstr)
				errx(1, "rtable %s: %s", errstr, optarg);
			break;
		case 'v':
			vflag = 1;
			break;
		case 'w':
			timeout = strtonum(optarg, 0, INT_MAX / 1000, &errstr);
			if (errstr)
				errx(1, "timeout %s: %s", errstr, optarg);
			timeout *= 1000;
			break;
		case 'x':
			xflag = 1;
			if ((proxy = strdup(optarg)) == NULL)
				err(1, NULL);
			break;
		case 'z':
			zflag = 1;
			break;
		case 'D':
			Dflag = 1;
			break;
		case 'I':
			Iflag = strtonum(optarg, 1, 65536 << 14, &errstr);
			if (errstr != NULL)
				errx(1, "TCP receive window %s: %s",
				    errstr, optarg);
			break;
		case 'O':
			Oflag = strtonum(optarg, 1, 65536 << 14, &errstr);
			if (errstr != NULL) {
			    if (strcmp(errstr, "invalid") != 0)
				errx(1, "TCP send window %s: %s",
				    errstr, optarg);
			}
			break;
		case 'S':
			Sflag = 1;
			break;
		case 'T':
			errstr = NULL;
			errno = 0;
			if (map_tos(optarg, &Tflag))
				break;
			if (strlen(optarg) > 1 && optarg[0] == '0' &&
			    optarg[1] == 'x')
				Tflag = (int)strtol(optarg, NULL, 16);
			else
				Tflag = (int)strtonum(optarg, 0, 255,
				    &errstr);
			if (Tflag < 0 || Tflag > 255 || errstr || errno)
				errx(1, "illegal tos value %s", optarg);
			break;
		default:
			usage(1);
		}
	}
	argc -= optind;
	argv += optind;

	/* Cruft to make sure options are clean, and used properly. */
	if (argv[0] && !argv[1] && family == AF_UNIX) {
		host = argv[0];
		uport = NULL;
	} else if (argv[0] && !argv[1]) {
		if  (!lflag)
			usage(1);
		uport = argv[0];
		host = NULL;
	} else if (argv[0] && argv[1]) {
		host = argv[0];
		uport = argv[1];
	} else
		usage(1);

	if (lflag && sflag)
		errx(1, "cannot use -s and -l");
	if (lflag && pflag)
		errx(1, "cannot use -p and -l");
	if (lflag && zflag)
		errx(1, "cannot use -z and -l");
	if (!lflag && kflag)
		errx(1, "must use -l with -k");

	/* Get name of temporary socket for unix datagram client */
	if ((family == AF_UNIX) && uflag && !lflag) {
		if (sflag) {
			unix_dg_tmp_socket = sflag;
		} else {
			strlcpy(unix_dg_tmp_socket_buf, "/tmp/nc.XXXXXXXXXX",
				UNIX_DG_TMP_SOCKET_SIZE);
			if (mktemp(unix_dg_tmp_socket_buf) == NULL)
				err(1, "mktemp");
			unix_dg_tmp_socket = unix_dg_tmp_socket_buf;
		}
	}

	/* Initialize addrinfo structure. */
	if (family != AF_UNIX) {
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = family;
		hints.ai_socktype = uflag ? SOCK_DGRAM : SOCK_STREAM;
		hints.ai_protocol = uflag ? IPPROTO_UDP : IPPROTO_TCP;
		if (nflag)
			hints.ai_flags |= AI_NUMERICHOST;
	}

	if (xflag) {
		if (uflag)
			errx(1, "no proxy support for UDP mode");

		if (lflag)
			errx(1, "no proxy support for listen");

		if (family == AF_UNIX)
			errx(1, "no proxy support for unix sockets");

		/* XXX IPv6 transport to proxy would probably work */
		if (family == AF_INET6)
			errx(1, "no proxy support for IPv6");

		if (sflag)
			errx(1, "no proxy support for local source address");

		proxyhost = strsep(&proxy, ":");
		proxyport = proxy;

		memset(&proxyhints, 0, sizeof(struct addrinfo));
		proxyhints.ai_family = family;
		proxyhints.ai_socktype = SOCK_STREAM;
		proxyhints.ai_protocol = IPPROTO_TCP;
		if (nflag)
			proxyhints.ai_flags |= AI_NUMERICHOST;
	}

	if (lflag) {
		int connfd;
		ret = 0;

		if (family == AF_UNIX) {
			if (uflag)
				s = unix_bind(host);
			else
				s = unix_listen(host);
		}

		/* Allow only one connection at a time, but stay alive. */
		for (;;) {
			if (family != AF_UNIX)
				s = local_listen(host, uport, hints);
			if (s < 0)
				err(1, NULL);
			/*
			 * For UDP and -k, don't connect the socket, let it
			 * receive datagrams from multiple socket pairs.
			 */
			if (uflag && kflag)
				readwrite(s);
			/*
			 * For UDP and not -k, we will use recvfrom() initially
			 * to wait for a caller, then use the regular functions
			 * to talk to the caller.
			 */
			else if (uflag && !kflag) {
				int rv, plen;
				char buf[16384];
				struct sockaddr_storage z;

				len = sizeof(z);
				plen = 2048;
				rv = recvfrom(s, buf, plen, MSG_PEEK,
				    (struct sockaddr *)&z, &len);
				if (rv < 0)
					err(1, "recvfrom");

				rv = connect(s, (struct sockaddr *)&z, len);
				if (rv < 0)
					err(1, "connect");

				if (vflag)
					report_connect((struct sockaddr *)&z, len);

				readwrite(s);
			} else {
				len = sizeof(cliaddr);
				connfd = accept(s, (struct sockaddr *)&cliaddr,
				    &len);
				if (connfd == -1) {
					/* For now, all errnos are fatal */
					err(1, "accept");
				}
				if (vflag)
					report_connect((struct sockaddr *)&cliaddr, len);

				readwrite(connfd);
				close(connfd);
			}

			if (family != AF_UNIX)
				close(s);
			else if (uflag) {
				if (connect(s, NULL, 0) < 0)
					err(1, "connect");
			}

			if (!kflag)
				break;
		}
	} else if (family == AF_UNIX) {
		ret = 0;

		if ((s = unix_connect(host)) > 0 && !zflag) {
			readwrite(s);
			close(s);
		} else
			ret = 1;

		if (uflag)
			unlink(unix_dg_tmp_socket);
		exit(ret);

	} else {
		int i = 0;

		/* Construct the portlist[] array. */
		build_ports(uport);

		/* Cycle through portlist, connecting to each port. */
		for (i = 0; portlist[i] != NULL; i++) {
			if (s)
				close(s);

			if (xflag)
				s = socks_connect(host, portlist[i], hints,
				    proxyhost, proxyport, proxyhints, socksv,
				    Pflag);
			else
				s = remote_connect(host, portlist[i], hints);

			if (s < 0)
				continue;

			ret = 0;
			if (vflag || zflag) {
				/* For UDP, make sure we are connected. */
				if (uflag) {
					if (udptest(s) == -1) {
						ret = 1;
						continue;
					}
				}

				/* Don't look up port if -n. */
				if (nflag)
					sv = NULL;
				else {
					sv = getservbyport(
					    ntohs(atoi(portlist[i])),
					    uflag ? "udp" : "tcp");
				}

				fprintf(stderr,
				    "Connection to %s %s port [%s/%s] "
				    "succeeded!\n", host, portlist[i],
				    uflag ? "udp" : "tcp",
				    sv ? sv->s_name : "*");
			}
			if (Fflag)
				fdpass(s);
			else if (!zflag)
				readwrite(s);
		}
	}

	if (s)
		close(s);

	exit(ret);
}