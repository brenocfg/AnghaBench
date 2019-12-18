#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bufferevent {int /*<<< orphan*/  ev_base; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_async {int write_added; TYPE_1__ bev; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_add_virtual_ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bev_async_add_write(struct bufferevent_async *beva)
{
	struct bufferevent *bev = &beva->bev.bev;

	if (!beva->write_added) {
		beva->write_added = 1;
		event_base_add_virtual_(bev->ev_base);
	}
}