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
struct pingpong_dest {int lid; int qpn; int psn; int /*<<< orphan*/  gid; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int MAX_QP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo_null (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  gid_to_wire_gid (int /*<<< orphan*/ *,char*) ; 
 struct pingpong_dest* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wire_gid_to_gid (char*,int /*<<< orphan*/ *) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static struct pingpong_dest *pp_client_exch_dest(const char *servername, int port,
						 const struct pingpong_dest *my_dest)
{
	struct addrinfo *res, *t;
	struct addrinfo hints = {
		.ai_family   = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM
	};
	char *service;
	char msg[sizeof "0000:000000:000000:00000000000000000000000000000000"];
	int n;
	int r;
	int i;
	int sockfd = -1;
	struct pingpong_dest *rem_dest = NULL;
	char gid[33];

	if (asprintf(&service, "%d", port) < 0)
		return NULL;

	n = getaddrinfo(servername, service, &hints, &res);

	if (n < 0) {
		fprintf(stderr, "%s for %s:%d\n", gai_strerror(n), servername, port);
		free(service);
		return NULL;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);
		if (sockfd >= 0) {
			if (!connect(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo_null(res);
	free(service);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't connect to %s:%d\n", servername, port);
		return NULL;
	}

	for (i = 0; i < MAX_QP; ++i) {
		gid_to_wire_gid(&my_dest[i].gid, gid);
		sprintf(msg, "%04x:%06x:%06x:%s", my_dest[i].lid,
					my_dest[i].qpn, my_dest[i].psn, gid);
		if (write(sockfd, msg, sizeof msg) != sizeof msg) {
			fprintf(stderr, "Couldn't send local address\n");
			goto out;
		}
	}

	rem_dest = malloc(MAX_QP * sizeof *rem_dest);
	if (!rem_dest)
		goto out;

	for (i = 0; i < MAX_QP; ++i) {
		n = 0;
		while (n < sizeof msg) {
			r = read(sockfd, msg + n, sizeof msg - n);
			if (r < 0) {
				perror("client read");
				fprintf(stderr, "%d/%d: Couldn't read remote address [%d]\n",
					n, (int) sizeof msg, i);
				goto out;
			}
			n += r;
		}

		sscanf(msg, "%x:%x:%x:%s", &rem_dest[i].lid, &rem_dest[i].qpn,
							&rem_dest[i].psn, gid);
		wire_gid_to_gid(gid, &rem_dest[i].gid);
	}

	if (write(sockfd, "done", sizeof "done") != sizeof "done") {
		perror("client write");
		goto out;
	}
out:
	close(sockfd);
	return rem_dest;
}