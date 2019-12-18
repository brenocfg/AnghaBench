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
struct basic_test_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct bufferevent* bufferevent_filter_new (struct bufferevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 struct bufferevent* bufferevent_socket_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_assert (struct bufferevent*) ; 

__attribute__((used)) static void
test_bufferevent_socket_filter_inactive(void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *bev = NULL, *bevf = NULL;

	bev = bufferevent_socket_new(data->base, -1, 0);
	tt_assert(bev);
	bevf = bufferevent_filter_new(bev, NULL, NULL, 0, NULL, NULL);
	tt_assert(bevf);

end:
	if (bevf)
		bufferevent_free(bevf);
	if (bev)
		bufferevent_free(bev);
}