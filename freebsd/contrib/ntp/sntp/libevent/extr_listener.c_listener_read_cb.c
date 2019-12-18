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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct evconnlistener {int refcnt; void* user_data; int /*<<< orphan*/  (* errorcb ) (struct evconnlistener*,void*) ;int /*<<< orphan*/  (* cb ) (struct evconnlistener*,scalar_t__,struct sockaddr*,int,void*) ;int /*<<< orphan*/  accept4_flags; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  (* evconnlistener_errorcb ) (struct evconnlistener*,void*) ;
typedef  int /*<<< orphan*/  (* evconnlistener_cb ) (struct evconnlistener*,scalar_t__,struct sockaddr*,int,void*) ;
typedef  scalar_t__ ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ EVUTIL_ERR_ACCEPT_RETRIABLE (int) ; 
 int /*<<< orphan*/  LOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  event_sock_warn (scalar_t__,char*) ; 
 scalar_t__ evutil_accept4_ (scalar_t__,struct sockaddr*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int evutil_socket_geterror (scalar_t__) ; 
 int listener_decref_and_unlock (struct evconnlistener*) ; 

__attribute__((used)) static void
listener_read_cb(evutil_socket_t fd, short what, void *p)
{
	struct evconnlistener *lev = p;
	int err;
	evconnlistener_cb cb;
	evconnlistener_errorcb errorcb;
	void *user_data;
	LOCK(lev);
	while (1) {
		struct sockaddr_storage ss;
		ev_socklen_t socklen = sizeof(ss);
		evutil_socket_t new_fd = evutil_accept4_(fd, (struct sockaddr*)&ss, &socklen, lev->accept4_flags);
		if (new_fd < 0)
			break;
		if (socklen == 0) {
			/* This can happen with some older linux kernels in
			 * response to nmap. */
			evutil_closesocket(new_fd);
			continue;
		}

		if (lev->cb == NULL) {
			evutil_closesocket(new_fd);
			UNLOCK(lev);
			return;
		}
		++lev->refcnt;
		cb = lev->cb;
		user_data = lev->user_data;
		UNLOCK(lev);
		cb(lev, new_fd, (struct sockaddr*)&ss, (int)socklen,
		    user_data);
		LOCK(lev);
		if (lev->refcnt == 1) {
			int freed = listener_decref_and_unlock(lev);
			EVUTIL_ASSERT(freed);

			evutil_closesocket(new_fd);
			return;
		}
		--lev->refcnt;
	}
	err = evutil_socket_geterror(fd);
	if (EVUTIL_ERR_ACCEPT_RETRIABLE(err)) {
		UNLOCK(lev);
		return;
	}
	if (lev->errorcb != NULL) {
		++lev->refcnt;
		errorcb = lev->errorcb;
		user_data = lev->user_data;
		UNLOCK(lev);
		errorcb(lev, user_data);
		LOCK(lev);
		listener_decref_and_unlock(lev);
	} else {
		event_sock_warn(fd, "Error from accept() call");
	}
}