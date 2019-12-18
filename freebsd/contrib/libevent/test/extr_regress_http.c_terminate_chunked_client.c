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
struct terminate_state {int /*<<< orphan*/  fd; int /*<<< orphan*/  bev; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
terminate_chunked_client(evutil_socket_t fd, short event, void *arg)
{
	struct terminate_state *state = arg;
	bufferevent_free(state->bev);
	evutil_closesocket(state->fd);
}