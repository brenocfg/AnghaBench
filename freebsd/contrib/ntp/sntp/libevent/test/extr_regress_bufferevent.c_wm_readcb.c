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
struct evbuffer {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_read_buffer (struct bufferevent*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
wm_readcb(struct bufferevent *bev, void *arg)
{
	struct evbuffer *evbuf = evbuffer_new();
	int len = (int)evbuffer_get_length(bev->input);
	static int nread;

	assert(len >= 10 && len <= 20);

	assert(evbuf != NULL);

	/* gratuitous test of bufferevent_read_buffer */
	bufferevent_read_buffer(bev, evbuf);

	nread += len;
	if (nread == 65000) {
		bufferevent_disable(bev, EV_READ);
		test_ok++;
	}

	evbuffer_free(evbuf);
}