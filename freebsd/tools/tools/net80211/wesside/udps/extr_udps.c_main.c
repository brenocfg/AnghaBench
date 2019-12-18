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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  s_in ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 char* inet_ntoa (TYPE_1__) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  own (int,struct sockaddr_in*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pps ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

int main(int argc, char* argv[]) {
	int port = 6969;
	struct sockaddr_in s_in;
	int s;
	int rd;
	int len;
	char buf[64];
	struct timeval tv;
	int do_it = 0;
	fd_set rfds;
	char ip[17];

	if( argc > 1)
		pps = atoi(argv[1]);

	printf("Packets per second=%d\n", pps);	

	s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if( s < 0)
		err(1, "socket()");

	s_in.sin_family = PF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;

	if( bind(s, (struct sockaddr*)&s_in, sizeof(s_in)) < 0) {
		perror("bind()");
		exit(1);
	}

	while(1) {
		assert(do_it >= 0);
		len = sizeof(struct sockaddr_in);

		memset(&tv, 0, sizeof(tv));
		tv.tv_usec = 1000*10;
		FD_ZERO(&rfds);
		FD_SET(s, &rfds);
		rd = select(s + 1, &rfds, NULL ,NULL ,&tv);
		if (rd == -1) {
			perror("select()");
			exit(1);
		}
		if (rd == 1 && FD_ISSET(s, &rfds)) {
			rd = recvfrom(s, buf, 64, 0, (struct sockaddr*)&s_in, &len);

			if(rd < 0) {
				perror("read died");
				exit(1);
			}

			if(rd == 5 && memcmp(buf, "sorbo", 5) == 0) {
				sprintf(ip, "%s", inet_ntoa(s_in.sin_addr));
				printf("Got signal from %s\n", ip);
#ifdef INSANE
				do_it = 10;
#else				
				do_it = 2;
#endif				
			}	
		}		

		if (do_it) {	
			printf("Sending stuff to %s\n", ip);

			own(s, &s_in);
			do_it--;

			if(do_it == 0)
			printf("Stopping send\n");
		}
	}
}