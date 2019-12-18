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
struct td_desc {int byte_count; int /*<<< orphan*/  count; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int POLLIN ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
rx_body(void *data)
{
	struct td_desc *t = data;
	struct pollfd fds;
	int y;

	fds.fd = t->fd;
	fds.events = POLLIN;

	for (;;) {
		if (poll(&fds, 1, -1) < 0) 
			perror("poll on thread");
		if (!(fds.revents & POLLIN))
			continue;
		for (;;) {
			y = recv(t->fd, t->buf, t->buflen, MSG_DONTWAIT);
			if (y < 0)
				break;
			t->count++;
			t->byte_count += y;
		}
	}
	return NULL;
}