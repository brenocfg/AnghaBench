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
struct evhttp_request {void (* on_complete_cb ) (struct evhttp_request*,void*) ;void* on_complete_cb_arg; } ;

/* Variables and functions */

void
evhttp_request_set_on_complete_cb(struct evhttp_request *req,
    void (*cb)(struct evhttp_request *, void *), void *cb_arg)
{
	req->on_complete_cb = cb;
	req->on_complete_cb_arg = cb_arg;
}