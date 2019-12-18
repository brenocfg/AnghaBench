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
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writecb_finished ; 

__attribute__((used)) static void
writecb(struct bufferevent *bev, void *arg)
{
	if (evbuffer_get_length(bufferevent_get_output(bev)) == 0) {
		++writecb_finished;
	}
}