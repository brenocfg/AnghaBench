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
typedef  int /*<<< orphan*/  remoteaddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int errno ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{

	int ch, cli_sock, count = 0;
	int port = PORT;
	struct sockaddr_in remoteaddr;

	while ((ch = getopt(argc, argv, "p:")) != -1) {
		switch (ch) {
		case 'p':
			port = atoi(optarg);
			break;
		case 'h':
		default:
			usage();
		}
	}

	bzero(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_len = sizeof(remoteaddr);
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_port = htons(port);
	remoteaddr.sin_addr.s_addr = INADDR_ANY;

	cli_sock = socket(AF_INET, SOCK_STREAM, 0);

	while ((cli_sock = connect(cli_sock, (struct sockaddr *)&remoteaddr,
				   sizeof(remoteaddr))) >= 0) {
		count++;
		close(cli_sock);
		cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	}

	printf("Exiting at %d with errno %d\n", count, errno);

}