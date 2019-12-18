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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int BUFFERSIZE ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
handle_connection(int accept_sock)
{
	u_char buffer[BUFFERSIZE];
	ssize_t len, recvlen, sofar;
	int s;

	s = accept(accept_sock, NULL, NULL);
	if (s < 0) {
		warn("accept");
		return;
	}

	while (1) {
		recvlen = recv(s, buffer, BUFFERSIZE, 0);
		if (recvlen < 0 || recvlen == 0) {
			close(s);
			return;
		}
		sofar = 0;
		while (sofar < recvlen) {
			len = send(s, buffer + sofar, recvlen - sofar, 0);
			if (len < 0) {
				close(s);
				return;
			}
			sofar += len;
		}
	}
}