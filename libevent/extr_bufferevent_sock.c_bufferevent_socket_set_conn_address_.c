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
struct sockaddr {int dummy; } ;
struct bufferevent_private {int /*<<< orphan*/  conn_address; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 

void
bufferevent_socket_set_conn_address_(struct bufferevent *bev,
	struct sockaddr *addr, size_t addrlen)
{
	struct bufferevent_private *bev_p = BEV_UPCAST(bev);
	EVUTIL_ASSERT(addrlen <= sizeof(bev_p->conn_address));
	memcpy(&bev_p->conn_address, addr, addrlen);
}