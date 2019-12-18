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
struct evhttp {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 struct evhttp* evhttp_new (struct event_base*) ; 
 int /*<<< orphan*/  evhttp_set_cb (struct evhttp*,char*,int /*<<< orphan*/ ,struct event_base*) ; 
 int /*<<< orphan*/  http_badreq_cb ; 
 int /*<<< orphan*/  http_basic_cb ; 
 scalar_t__ http_bind (struct evhttp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  http_chunked_cb ; 
 int /*<<< orphan*/  http_delay_cb ; 
 int /*<<< orphan*/  http_delete_cb ; 
 int /*<<< orphan*/  http_dispatcher_cb ; 
 int /*<<< orphan*/  http_large_delay_cb ; 
 int /*<<< orphan*/  http_on_complete_cb ; 
 int /*<<< orphan*/  http_post_cb ; 
 int /*<<< orphan*/  http_put_cb ; 

__attribute__((used)) static struct evhttp *
http_setup(ev_uint16_t *pport, struct event_base *base, int ipv6)
{
	struct evhttp *myhttp;

	/* Try a few different ports */
	myhttp = evhttp_new(base);

	if (http_bind(myhttp, pport, ipv6) < 0)
		return NULL;

	/* Register a callback for certain types of requests */
	evhttp_set_cb(myhttp, "/test", http_basic_cb, base);
	evhttp_set_cb(myhttp, "/chunked", http_chunked_cb, base);
	evhttp_set_cb(myhttp, "/streamed", http_chunked_cb, base);
	evhttp_set_cb(myhttp, "/postit", http_post_cb, base);
	evhttp_set_cb(myhttp, "/putit", http_put_cb, base);
	evhttp_set_cb(myhttp, "/deleteit", http_delete_cb, base);
	evhttp_set_cb(myhttp, "/delay", http_delay_cb, base);
	evhttp_set_cb(myhttp, "/largedelay", http_large_delay_cb, base);
	evhttp_set_cb(myhttp, "/badrequest", http_badreq_cb, base);
	evhttp_set_cb(myhttp, "/oncomplete", http_on_complete_cb, base);
	evhttp_set_cb(myhttp, "/", http_dispatcher_cb, base);
	return (myhttp);
}