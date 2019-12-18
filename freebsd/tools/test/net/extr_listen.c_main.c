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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  localaddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int LISTEN ; 
 int PORT ; 
 int RECV_LIMIT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{

	int ch, srv_sock, cli_sock, recvd = 0;
	int port = PORT;
	int limit = LISTEN;
	struct sockaddr_in localaddr;

	while ((ch = getopt(argc, argv, "p:l:")) != -1) {
		switch (ch) {
		case 'p':
			port = atoi(optarg);
			break;
		case 'l':
			limit = atoi(optarg);
                     break;
		case 'h':
		default:
			usage();
		}
	}

	bzero(&localaddr, sizeof(localaddr));
	localaddr.sin_len = sizeof(localaddr);
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(port);
	localaddr.sin_addr.s_addr = INADDR_ANY;

	srv_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(srv_sock, (struct sockaddr *)&localaddr,
		 sizeof(struct sockaddr_in)) < 0)
		err(EX_OSERR, "Could not bind to INADDR_ANY:%d", port);
	
	if (listen(srv_sock, limit) < 0)
		err(EX_OSERR, "Failed to listen with depth of %d\n", limit);
	
	while (((cli_sock = accept(srv_sock, NULL, NULL)) >= 0)
	       && (recvd < RECV_LIMIT)) {
		close(cli_sock);
		recvd++;
	}

	listen(srv_sock, 0);

	while (((cli_sock = accept(srv_sock, NULL, NULL)) >= 0)
	    && (recvd <= (RECV_LIMIT + limit + 1))) {
		close(cli_sock);
		recvd++;
	}

	if (accept(srv_sock, NULL, NULL) >= 0)
		printf ("Late connection at %d\n", recvd);
	else
		printf("recvd %d\n", recvd);
}