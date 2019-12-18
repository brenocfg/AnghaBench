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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  TEST_SECONDS ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ accept_socket ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  cancel_alarm () ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 scalar_t__ listen_socket ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ receive_test () ; 
 int /*<<< orphan*/  setup_alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_child(void)
{
	struct sockaddr_in sin;
	int rc = 0;

	listen_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_socket < 0) {
		printf("# socket: %s\n", strerror(errno));
		rc = -1;
	}

	if (!rc) {
		bzero(&sin, sizeof(sin));
		sin.sin_len = sizeof(sin);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		sin.sin_port = htons(TEST_PORT);

		if (bind(listen_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			printf("# bind: %s\n", strerror(errno));
			rc = -1;
		}
	}

	if (!rc && listen(listen_socket, -1) < 0) {
		printf("# listen: %s\n", strerror(errno));
		rc = -1;
	}

	if (!rc) {
		accept_socket = accept(listen_socket, NULL, NULL);	
		setup_alarm(TEST_SECONDS);
		if (receive_test() != 0)
			rc = -1;
	}

	cancel_alarm();
	if (accept_socket > 0)
		close(accept_socket);
	if (listen_socket > 0)
		close(listen_socket);

	_exit(rc);
}