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
typedef  int /*<<< orphan*/  v ;
typedef  int u_short ;
struct td_desc {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int MAXSOCK ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char const* gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 int /*<<< orphan*/  main_thread (struct td_desc**,int,int) ; 
 struct td_desc** make_threads (int*,int,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct addrinfo hints, *res, *res0;
	char *dummy, *packet;
	int port;
	int error, v, nthreads = 1;
	struct td_desc **tp;
	const char *cause = NULL;
	int s[MAXSOCK];
	int nsock;

	if (argc < 2)
		usage();

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	port = strtoul(argv[1], &dummy, 10);
	if (port < 1 || port > 65535 || *dummy != '\0')
		usage();
	if (argc > 2)
		nthreads = strtoul(argv[2], &dummy, 10);
	if (nthreads < 1 || nthreads > 64)
		usage();

	packet = malloc(65536);
	if (packet == NULL) {
		perror("malloc");
		return (-1);
	}
	bzero(packet, 65536);

	error = getaddrinfo(NULL, argv[1], &hints, &res0);
	if (error) {
		perror(gai_strerror(error));
		return (-1);
		/*NOTREACHED*/
	}

	nsock = 0;
	for (res = res0; res && nsock < MAXSOCK; res = res->ai_next) {
		s[nsock] = socket(res->ai_family, res->ai_socktype,
		res->ai_protocol);
		if (s[nsock] < 0) {
			cause = "socket";
			continue;
		}

		v = 128 * 1024;
		if (setsockopt(s[nsock], SOL_SOCKET, SO_RCVBUF, &v, sizeof(v)) < 0) {
			cause = "SO_RCVBUF";
			close(s[nsock]);
			continue;
		}
		if (bind(s[nsock], res->ai_addr, res->ai_addrlen) < 0) {
			cause = "bind";
			close(s[nsock]);
			continue;
		}
		(void) listen(s[nsock], 5);
		nsock++;
	}
	if (nsock == 0) {
		perror(cause);
		return (-1);
		/*NOTREACHED*/
	}

	printf("netreceive %d sockets x %d threads listening on UDP port %d\n",
		nsock, nthreads, (u_short)port);

	tp = make_threads(s, nsock, nthreads);
	main_thread(tp, nsock, nthreads);

	/*NOTREACHED*/
	freeaddrinfo(res0);
}