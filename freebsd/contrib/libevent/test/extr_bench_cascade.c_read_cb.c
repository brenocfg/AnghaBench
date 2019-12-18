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
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_intptr_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  fired ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_cb(evutil_socket_t fd, short which, void *arg)
{
	char ch;
	evutil_socket_t sock = (evutil_socket_t)(ev_intptr_t)arg;

	(void) recv(fd, &ch, sizeof(ch), 0);
	if (sock >= 0) {
		if (send(sock, "e", 1, 0) < 0)
			perror("send");
	}
	fired++;
}