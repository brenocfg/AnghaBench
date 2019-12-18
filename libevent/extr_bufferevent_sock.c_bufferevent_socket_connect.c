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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct bufferevent_private {int connecting; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; int /*<<< orphan*/  ev_write; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_ERROR ; 
 scalar_t__ BEV_IS_ASYNC (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_OPT_DEFER_CALLBACKS ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int EVUTIL_SOCK_NONBLOCK ; 
 int EV_FINALIZE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  be_socket_enable (struct bufferevent*,int) ; 
 scalar_t__ bufferevent_async_can_connect_ (struct bufferevent*) ; 
 int bufferevent_async_connect_ (struct bufferevent*,scalar_t__,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int) ; 
 scalar_t__ bufferevent_getfd (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_setfd (struct bufferevent*,scalar_t__) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_writecb ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 scalar_t__ evutil_socket_ (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int evutil_socket_connect_ (scalar_t__*,struct sockaddr const*,int) ; 

int
bufferevent_socket_connect(struct bufferevent *bev,
    const struct sockaddr *sa, int socklen)
{
	struct bufferevent_private *bufev_p = BEV_UPCAST(bev);

	evutil_socket_t fd;
	int r = 0;
	int result=-1;
	int ownfd = 0;

	bufferevent_incref_and_lock_(bev);

	fd = bufferevent_getfd(bev);
	if (fd < 0) {
		if (!sa)
			goto done;
		fd = evutil_socket_(sa->sa_family,
		    SOCK_STREAM|EVUTIL_SOCK_NONBLOCK, 0);
		if (fd < 0)
			goto freesock;
		ownfd = 1;
	}
	if (sa) {
#ifdef _WIN32
		if (bufferevent_async_can_connect_(bev)) {
			bufferevent_setfd(bev, fd);
			r = bufferevent_async_connect_(bev, fd, sa, socklen);
			if (r < 0)
				goto freesock;
			bufev_p->connecting = 1;
			result = 0;
			goto done;
		} else
#endif
		r = evutil_socket_connect_(&fd, sa, socklen);
		if (r < 0)
			goto freesock;
	}
#ifdef _WIN32
	/* ConnectEx() isn't always around, even when IOCP is enabled.
	 * Here, we borrow the socket object's write handler to fall back
	 * on a non-blocking connect() when ConnectEx() is unavailable. */
	if (BEV_IS_ASYNC(bev)) {
		event_assign(&bev->ev_write, bev->ev_base, fd,
		    EV_WRITE|EV_PERSIST|EV_FINALIZE, bufferevent_writecb, bev);
	}
#endif
	bufferevent_setfd(bev, fd);
	if (r == 0) {
		if (! be_socket_enable(bev, EV_WRITE)) {
			bufev_p->connecting = 1;
			result = 0;
			goto done;
		}
	} else if (r == 1) {
		/* The connect succeeded already. How very BSD of it. */
		result = 0;
		bufev_p->connecting = 1;
		bufferevent_trigger_nolock_(bev, EV_WRITE, BEV_OPT_DEFER_CALLBACKS);
	} else {
		/* The connect failed already.  How very BSD of it. */
		result = 0;
		bufferevent_run_eventcb_(bev, BEV_EVENT_ERROR, BEV_OPT_DEFER_CALLBACKS);
		bufferevent_disable(bev, EV_WRITE|EV_READ);
	}

	goto done;

freesock:
	if (ownfd)
		evutil_closesocket(fd);
done:
	bufferevent_decref_and_unlock_(bev);
	return result;
}