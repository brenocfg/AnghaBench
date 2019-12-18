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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int blast_loop (int,long,char*,long) ; 
 int /*<<< orphan*/  bzero (char*,long) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char const* gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 char* malloc (long) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	long payloadsize, duration;
	struct addrinfo hints, *res, *res0;
	char *dummy, *packet;
	int port, s, error;
	const char *cause = NULL;

	if (argc != 5)
		usage();

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	port = strtoul(argv[2], &dummy, 10);
	if (port < 1 || port > 65535 || *dummy != '\0') {
		fprintf(stderr, "Invalid port number: %s\n", argv[2]);
		usage();
		/*NOTREACHED*/
	}

	payloadsize = strtoul(argv[3], &dummy, 10);
	if (payloadsize < 0 || *dummy != '\0')
		usage();
	if (payloadsize > 32768) {
		fprintf(stderr, "payloadsize > 32768\n");
		return (-1);
		/*NOTREACHED*/
	}

	duration = strtoul(argv[4], &dummy, 10);
	if (duration < 0 || *dummy != '\0') {
		fprintf(stderr, "Invalid duration time: %s\n", argv[4]);
		usage();
		/*NOTREACHED*/
	}

	packet = malloc(payloadsize);
	if (packet == NULL) {
		perror("malloc");
		return (-1);
		/*NOTREACHED*/
	}

	bzero(packet, payloadsize);
	error = getaddrinfo(argv[1],argv[2], &hints, &res0);
	if (error) {
		perror(gai_strerror(error));
		return (-1);
		/*NOTREACHED*/
	}
	s = -1;
	for (res = res0; res; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype, 0);
		if (s < 0) {
			cause = "socket";
			continue;
		}

		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			cause = "connect";
			close(s);
			s = -1;
			continue;
		}

		break;  /* okay we got one */
	}
	if (s < 0) {
		perror(cause);
		return (-1);
		/*NOTREACHED*/
	}

	freeaddrinfo(res0);

	return (blast_loop(s, duration, packet, payloadsize));

}