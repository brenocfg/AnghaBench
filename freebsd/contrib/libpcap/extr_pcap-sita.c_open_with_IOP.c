#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ip; int fd; int find_fd; scalar_t__ first_time; TYPE_4__* serv_addr; } ;
typedef  TYPE_2__ unit_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IOP_SNIFFER_PORT ; 
 int LIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int open_with_IOP(unit_t  *u, int flag) {
	int					sockfd;
	char				*ip;

	if (u->serv_addr == NULL) {
		u->serv_addr = malloc(sizeof(struct sockaddr_in));

		/* since we called malloc(), lets check to see if we actually got the memory	*/
		if (u->serv_addr == NULL) {	/* oops, we didn't get the memory requested	*/
			fprintf(stderr, "malloc() request for u->serv_addr failed, value of errno is: %d\n", errno);
			return 0;
		}

	}
	ip = u->ip;
	/* bzero() is deprecated, replaced with memset()	*/
	memset((char *)u->serv_addr, 0, sizeof(struct sockaddr_in));
	u->serv_addr->sin_family		= AF_INET;
	u->serv_addr->sin_addr.s_addr	= inet_addr(ip);
	u->serv_addr->sin_port			= htons(IOP_SNIFFER_PORT);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "pcap can't open a socket for connecting to IOP at %s\n", ip);
		return 0;
	}
	if (connect(sockfd, (struct sockaddr *)u->serv_addr, sizeof(struct sockaddr_in)) < 0) {
		fprintf(stderr, "pcap can't connect to IOP at %s\n", ip);
		return 0;
	}
	if (flag == LIVE)	u->fd = sockfd;
	else				u->find_fd = sockfd;
	u->first_time = 0;
	return sockfd;			/* return the non-zero file descriptor as a 'success' indicator */
}