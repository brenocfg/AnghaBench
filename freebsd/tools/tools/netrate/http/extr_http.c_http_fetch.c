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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int BUFFER ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
http_fetch(struct sockaddr_in *sin, char *path, int quiet)
{
	u_char buffer[BUFFER];
	ssize_t len;
	size_t sofar;
	int sock;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		if (!quiet)
			warn("socket(PF_INET, SOCK_STREAM)");
		return (-1);
	}

	/* XXX: Mark non-blocking. */

	if (connect(sock, (struct sockaddr *)sin, sizeof(*sin)) < 0) {
		if (!quiet)
			warn("connect");
		close(sock);
		return (-1);
	}

	/* XXX: select for connection. */

	/* Send a request. */
	snprintf(buffer, BUFFER, "GET %s HTTP/1.0\n\n", path);
	sofar = 0;
	while (sofar < strlen(buffer)) {
		len = send(sock, buffer, strlen(buffer), 0);
		if (len < 0) {
			if (!quiet)
				warn("send");
			close(sock);
			return (-1);
		}
		if (len == 0) {
			if (!quiet)
				warnx("send: len == 0");
		}
		sofar += len;
	}

	/* Read until done.  Not very smart. */
	while (1) {
		len = recv(sock, buffer, BUFFER, 0);
		if (len < 0) {
			if (!quiet)
				warn("recv");
			close(sock);
			return (-1);
		}
		if (len == 0)
			break;
	}

	close(sock);
	return (0);
}