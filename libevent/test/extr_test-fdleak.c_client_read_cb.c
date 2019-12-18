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
struct event_base {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_REQUESTS ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 struct event_base* bufferevent_get_base (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_read (struct bufferevent*,unsigned char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ num_requests ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  start_client (struct event_base*) ; 

__attribute__((used)) static void
client_read_cb(struct bufferevent *bev, void *ctx)
{
	unsigned char tmp;
	struct event_base *base = bufferevent_get_base(bev);

	bufferevent_read(bev, &tmp, 1);
	if (tmp != 'A') {
		puts("Incorrect data received!");
		exit(2);
	}
	bufferevent_free(bev);

	num_requests++;
	if (++num_requests < MAX_REQUESTS) {
		start_client(base);
	}
}