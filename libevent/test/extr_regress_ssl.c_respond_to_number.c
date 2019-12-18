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
typedef  enum regress_openssl_type { ____Placeholder_regress_openssl_type } regress_openssl_type ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_EOL_LF ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int REGRESS_OPENSSL_CLIENT ; 
 int /*<<< orphan*/  SSL_renegotiate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  TT_FAIL (char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 struct evbuffer* bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_openssl_get_ssl (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*,int) ; 
 char* evbuffer_readln (struct evbuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int renegotiate_at ; 
 int /*<<< orphan*/  test_is_done ; 

__attribute__((used)) static void
respond_to_number(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *b = bufferevent_get_input(bev);
	char *line;
	int n;

	enum regress_openssl_type type;
	type = (enum regress_openssl_type)ctx;

	line = evbuffer_readln(b, NULL, EVBUFFER_EOL_LF);
	if (! line)
		return;
	n = atoi(line);
	if (n <= 0)
		TT_FAIL(("Bad number: %s", line));
	free(line);
	TT_BLATHER(("The number was %d", n));
	if (n == 1001) {
		++test_is_done;
		bufferevent_free(bev); /* Should trigger close on other side. */
		return;
	}
	if ((type & REGRESS_OPENSSL_CLIENT) && n == renegotiate_at) {
		SSL_renegotiate(bufferevent_openssl_get_ssl(bev));
	}
	++n;
	evbuffer_add_printf(bufferevent_get_output(bev),
	    "%d\n", n);
	TT_BLATHER(("Done reading; now writing."));
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_disable(bev, EV_READ);
}