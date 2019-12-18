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
struct event_overlapped {int /*<<< orphan*/  overlapped; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WSAGetOverlappedResult (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_overlapped_get_fd_ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bev_async_set_wsa_error(struct bufferevent *bev, struct event_overlapped *eo)
{
	DWORD bytes, flags;
	evutil_socket_t fd;

	fd = evbuffer_overlapped_get_fd_(bev->input);
	WSAGetOverlappedResult(fd, &eo->overlapped, &bytes, FALSE, &flags);
}