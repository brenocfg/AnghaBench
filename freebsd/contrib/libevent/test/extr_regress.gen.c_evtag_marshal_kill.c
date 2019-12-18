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
struct kill {int dummy; } ;
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evtag_marshal_buffer (struct evbuffer*,int /*<<< orphan*/ ,struct evbuffer*) ; 
 int /*<<< orphan*/  kill_marshal (struct evbuffer*,struct kill const*) ; 

void
evtag_marshal_kill(struct evbuffer *evbuf, ev_uint32_t tag, const struct kill *msg)
{
  struct evbuffer *buf_ = evbuffer_new();
  assert(buf_ != NULL);
  kill_marshal(buf_, msg);
  evtag_marshal_buffer(evbuf, tag, buf_);
   evbuffer_free(buf_);
}