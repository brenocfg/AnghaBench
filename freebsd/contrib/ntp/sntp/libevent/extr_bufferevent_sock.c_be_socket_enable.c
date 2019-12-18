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
struct bufferevent {int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  ev_read; } ;

/* Variables and functions */
 short EV_READ ; 
 short EV_WRITE ; 
 int be_socket_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
be_socket_enable(struct bufferevent *bufev, short event)
{
	if (event & EV_READ) {
		if (be_socket_add(&bufev->ev_read,&bufev->timeout_read) == -1)
			return -1;
	}
	if (event & EV_WRITE) {
		if (be_socket_add(&bufev->ev_write,&bufev->timeout_write) == -1)
			return -1;
	}
	return 0;
}