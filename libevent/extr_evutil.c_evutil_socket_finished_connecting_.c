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
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int ev_socklen_t ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 scalar_t__ EVUTIL_ERR_CONNECT_RETRIABLE (int) ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 

int
evutil_socket_finished_connecting_(evutil_socket_t fd)
{
	int e;
	ev_socklen_t elen = sizeof(e);

	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)&e, &elen) < 0)
		return -1;

	if (e) {
		if (EVUTIL_ERR_CONNECT_RETRIABLE(e))
			return 0;
		EVUTIL_SET_SOCKET_ERROR(e);
		return -1;
	}

	return 1;
}