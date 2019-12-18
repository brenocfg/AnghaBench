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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;
typedef  enum bufferevent_filter_result { ____Placeholder_bufferevent_filter_result } bufferevent_filter_result ;

/* Variables and functions */
 int BEV_ERROR ; 
 int BEV_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,...) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,unsigned int) ; 
 unsigned int evbuffer_get_length (struct evbuffer*) ; 
 unsigned char* evbuffer_pullup (struct evbuffer*,unsigned int) ; 
 int test_ok ; 

__attribute__((used)) static enum bufferevent_filter_result
bufferevent_output_filter(struct evbuffer *src, struct evbuffer *dst,
    ev_ssize_t lim, enum bufferevent_flush_mode state, void *ctx)
{
	const unsigned char *buffer;
	unsigned i;
	struct bufferevent **bevp = ctx;

	++test_ok;

	if (test_ok == 1) {
		buffer = evbuffer_pullup(src, evbuffer_get_length(src));
		for (i = 0; i < evbuffer_get_length(src); ++i) {
			evbuffer_add(dst, "x", 1);
			evbuffer_add(dst, buffer + i, 1);
		}
		evbuffer_drain(src, evbuffer_get_length(src));
	} else {
		return BEV_ERROR;
	}

	if (bevp && test_ok == 1) {
		int prev = ++test_ok;
		bufferevent_write(*bevp, "-", 1);
		/* check that during this bufferevent_write()
		 * bufferevent_output_filter() will not be called again */
		assert(test_ok == prev);
		--test_ok;
	}

	return (BEV_OK);
}