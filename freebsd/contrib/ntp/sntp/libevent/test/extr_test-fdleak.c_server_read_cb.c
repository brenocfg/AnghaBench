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
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_read (struct bufferevent*,unsigned char*,int) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,unsigned char*,int) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
server_read_cb(struct bufferevent *bev, void *ctx)
{
	while (evbuffer_get_length(bufferevent_get_input(bev))) {
		unsigned char tmp;
		bufferevent_read(bev, &tmp, 1);
		bufferevent_write(bev, &tmp, 1);
	}
}