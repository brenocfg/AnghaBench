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
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 scalar_t__ ENOPROTOOPT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LISTENQLIMIT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
test_set_qlimit(void)
{
	int i, ret, sock;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		err(-1, "test_set_qlimit: socket(PF_INET, SOCK_STREAM)");

	i = 0;
	ret = setsockopt(sock, SOL_SOCKET, SO_LISTENQLIMIT, &i, sizeof(i));
	if (ret < 0 && errno != ENOPROTOOPT) {
		warn("test_set_qlimit: setsockopt(SOL_SOCKET, "
		    "SO_LISTENQLIMIT, 0): unexpected error");
		close(sock);
	}

	if (ret == 0) {
		warnx("test_set_qlimit: setsockopt(SOL_SOCKET, "
		    "SO_LISTENQLIMIT, 0) succeeded");
		close(sock);
		exit(-1);
	}
	close(sock);
}