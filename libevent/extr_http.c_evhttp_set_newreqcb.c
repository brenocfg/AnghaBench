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
struct evhttp {int (* newreqcb ) (struct evhttp_request*,void*) ;void* newreqcbarg; } ;

/* Variables and functions */

void
evhttp_set_newreqcb(struct evhttp *http,
    int (*cb)(struct evhttp_request *, void *), void *cbarg)
{
	http->newreqcb = cb;
	http->newreqcbarg = cbarg;
}