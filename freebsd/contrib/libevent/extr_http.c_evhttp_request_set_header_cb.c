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
struct evhttp_request {int (* header_cb ) (struct evhttp_request*,void*) ;} ;

/* Variables and functions */

void
evhttp_request_set_header_cb(struct evhttp_request *req,
    int (*cb)(struct evhttp_request *, void *))
{
	req->header_cb = cb;
}