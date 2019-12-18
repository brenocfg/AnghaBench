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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ listen (int,int) ; 
 int socket (int,int,int) ; 
 scalar_t__ socket_get_backlog (int,int*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*,int,int) ; 

__attribute__((used)) static int
socket_listen(int domain, int type, int protocol, int backlog,
    int create_backlog_assertion, int listen_backlog_assertion, int *sockp,
    const char *domainstring, const char *typestring, const char *testclass,
    const char *test)
{
	int backlog_retrieved, sock;

	sock = socket(domain, type, protocol);
	if (sock < 0) {
		warn("%s: %s: socket_listen: socket(%s, %s)", testclass,
		    test, domainstring, typestring);
		close(sock);
		return (-1);
	}

	if (socket_get_backlog(sock, &backlog_retrieved, testclass, test,
	    "socket_listen") < 0) {
		close(sock);
		return (-1);
	}

	if (backlog_retrieved != create_backlog_assertion) {
		warnx("%s: %s: socket_listen: create backlog is %d not %d",
		    testclass, test, backlog_retrieved,
		    create_backlog_assertion);
		close(sock);
		return (-1);
	}

	if (listen(sock, backlog) < 0) {
		warn("%s: %s: socket_listen: listen(, %d)", testclass, test,
		    backlog);
		close(sock);
		return (-1);
	}

	if (socket_get_backlog(sock, &backlog_retrieved, testclass, test,
	    "socket_listen") < 0) {
		close(sock);
		return (-1);
	}

	if (backlog_retrieved != listen_backlog_assertion) {
		warnx("%s: %s: socket_listen: listen backlog is %d not %d",
		    testclass, test, backlog_retrieved,
		    listen_backlog_assertion);
		close(sock);
		return (-1);
	}

	*sockp = sock;
	return (0);
}