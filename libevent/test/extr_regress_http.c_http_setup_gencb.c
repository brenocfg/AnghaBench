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
typedef  struct evhttp event_base ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int HTTP_BIND_SSL ; 
 struct evhttp* evhttp_new (struct evhttp*) ; 
 int /*<<< orphan*/  evhttp_set_bevcb (struct evhttp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_set_cb (struct evhttp*,char*,int /*<<< orphan*/ ,struct evhttp*) ; 
 int /*<<< orphan*/  evhttp_set_ext_method_cmp (struct evhttp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_set_gencb (struct evhttp*,void (*) (struct evhttp_request*,void*),void*) ; 
 int /*<<< orphan*/  ext_method_cb ; 
 int /*<<< orphan*/  http_badreq_cb ; 
 int /*<<< orphan*/  http_basic_cb ; 
 scalar_t__ http_bind (struct evhttp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  http_chunked_cb ; 
 int /*<<< orphan*/  http_custom_cb ; 
 int /*<<< orphan*/  http_delay_cb ; 
 int /*<<< orphan*/  http_dispatcher_cb ; 
 int /*<<< orphan*/  http_genmethod_cb ; 
 int /*<<< orphan*/  http_large_cb ; 
 int /*<<< orphan*/  http_large_delay_cb ; 
 int /*<<< orphan*/  http_on_complete_cb ; 
 int /*<<< orphan*/  http_post_cb ; 
 int /*<<< orphan*/  http_put_cb ; 
 int /*<<< orphan*/  http_timeout_cb ; 
 int /*<<< orphan*/  https_bev ; 
 int /*<<< orphan*/  init_ssl () ; 

__attribute__((used)) static struct evhttp *
http_setup_gencb(ev_uint16_t *pport, struct event_base *base, int mask,
	void (*cb)(struct evhttp_request *, void *), void *cbarg)
{
	struct evhttp *myhttp;

	/* Try a few different ports */
	myhttp = evhttp_new(base);

	if (http_bind(myhttp, pport, mask) < 0)
		return NULL;
#ifdef EVENT__HAVE_OPENSSL
	if (mask & HTTP_BIND_SSL) {
		init_ssl();
		evhttp_set_bevcb(myhttp, https_bev, NULL);
	}
#endif

	evhttp_set_gencb(myhttp, cb, cbarg);

	/* add support for extended HTTP methods */
	evhttp_set_ext_method_cmp(myhttp, ext_method_cb);

	/* Register a callback for certain types of requests */
	evhttp_set_cb(myhttp, "/test", http_basic_cb, myhttp);
	evhttp_set_cb(myhttp, "/test nonconformant", http_basic_cb, myhttp);
	evhttp_set_cb(myhttp, "/timeout", http_timeout_cb, myhttp);
	evhttp_set_cb(myhttp, "/large", http_large_cb, base);
	evhttp_set_cb(myhttp, "/chunked", http_chunked_cb, base);
	evhttp_set_cb(myhttp, "/streamed", http_chunked_cb, base);
	evhttp_set_cb(myhttp, "/postit", http_post_cb, base);
	evhttp_set_cb(myhttp, "/putit", http_put_cb, base);
	evhttp_set_cb(myhttp, "/deleteit", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/propfind", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/proppatch", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/mkcol", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/lockit", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/unlockit", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/copyit", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/moveit", http_genmethod_cb, base);
	evhttp_set_cb(myhttp, "/custom", http_custom_cb, base);
	evhttp_set_cb(myhttp, "/delay", http_delay_cb, base);
	evhttp_set_cb(myhttp, "/largedelay", http_large_delay_cb, base);
	evhttp_set_cb(myhttp, "/badrequest", http_badreq_cb, base);
	evhttp_set_cb(myhttp, "/oncomplete", http_on_complete_cb, base);
	evhttp_set_cb(myhttp, "/", http_dispatcher_cb, base);
	return (myhttp);
}