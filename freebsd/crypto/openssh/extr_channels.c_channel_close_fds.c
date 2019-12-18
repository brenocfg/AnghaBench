#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_3__ {int sock; int rfd; int wfd; int efd; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  channel_close_fd (struct ssh*,int*) ; 

__attribute__((used)) static void
channel_close_fds(struct ssh *ssh, Channel *c)
{
	int sock = c->sock, rfd = c->rfd, wfd = c->wfd, efd = c->efd;

	channel_close_fd(ssh, &c->sock);
	if (rfd != sock)
		channel_close_fd(ssh, &c->rfd);
	if (wfd != sock && wfd != rfd)
		channel_close_fd(ssh, &c->wfd);
	if (efd != sock && efd != rfd && efd != wfd)
		channel_close_fd(ssh, &c->efd);
}