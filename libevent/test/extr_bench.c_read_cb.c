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
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int ev_ssize_t ;
typedef  int ev_intptr_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int count ; 
 int /*<<< orphan*/  failures ; 
 int /*<<< orphan*/  fired ; 
 int num_pipes ; 
 int /*<<< orphan*/ * pipes ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ writes ; 

__attribute__((used)) static void
read_cb(evutil_socket_t fd, short which, void *arg)
{
	ev_intptr_t idx = (ev_intptr_t) arg, widx = idx + 1;
	unsigned char ch;
	ev_ssize_t n;

	n = recv(fd, (char*)&ch, sizeof(ch), 0);
	if (n >= 0)
		count += n;
	else
		failures++;
	if (writes) {
		if (widx >= num_pipes)
			widx -= num_pipes;
		n = send(pipes[2 * widx + 1], "e", 1, 0);
		if (n != 1)
			failures++;
		writes--;
		fired++;
	}
}