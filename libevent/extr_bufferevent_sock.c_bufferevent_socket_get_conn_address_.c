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
typedef  struct sockaddr const sockaddr ;
struct bufferevent_private {int /*<<< orphan*/  conn_address; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 

const struct sockaddr*
bufferevent_socket_get_conn_address_(struct bufferevent *bev)
{
	struct bufferevent_private *bev_p = BEV_UPCAST(bev);
	return (struct sockaddr *)&bev_p->conn_address;
}