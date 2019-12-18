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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  s_in ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,struct sockaddr*,int*) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  hand ; 
 int /*<<< orphan*/  handle_dude (int,int) ; 
 int /*<<< orphan*/  htons (int) ; 
 char* inet_ntoa (TYPE_1__) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int s, dude;
	struct sockaddr_in s_in;
	int len;
	int raw;

	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = PF_INET;
	s_in.sin_port = htons(666);
	s_in.sin_addr.s_addr = INADDR_ANY;

	if ((raw = socket(PF_INET, SOCK_RAW, 0)) == -1)
		err(1, "socket()");

	if ((s = socket(s_in.sin_family, SOCK_STREAM, IPPROTO_TCP)) == -1)
		err(1, "socket()");

	if (bind(s, (struct sockaddr*)&s_in, sizeof(s_in)) == -1)
		err(1, "bind()");

	if (listen(s, 5) == -1)
		err(1, "listen()");

	if (signal(SIGPIPE, hand) == SIG_ERR)
		err(1, "signal()");

	while (1) {
		len = sizeof(s_in);
		dude = accept(s, (struct sockaddr*)&s_in, &len);
		if (dude == -1)
			err(1, "accept()");

		printf("Got dude %s\n", inet_ntoa(s_in.sin_addr));
		handle_dude(dude, raw);
		printf("Done\n");
	}
}