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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 short BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,unsigned char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
client_event_cb(struct bufferevent *bev, short events, void *ctx)
{
	if (events & BEV_EVENT_CONNECTED) {
		unsigned char tmp = 'A';
		bufferevent_write(bev, &tmp, 1);
	} else if (events & BEV_EVENT_ERROR) {
		puts("Client socket got error!");
		exit(2);
	}

	bufferevent_enable(bev, EV_READ);
}