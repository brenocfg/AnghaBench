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
struct msg {int dummy; } ;
struct kill {int dummy; } ;
struct evrpc_pool {int dummy; } ;
struct evrpc_base {int dummy; } ;
struct evhttp {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_MAKE_REQUEST (int /*<<< orphan*/ ,struct evrpc_pool*,struct msg*,struct kill*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVRPC_REQUEST_DONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTAG_ASSIGN (struct msg*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GotErrorCb ; 
 int /*<<< orphan*/  NeverReply ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int /*<<< orphan*/  evrpc_pool_free (struct evrpc_pool*) ; 
 int /*<<< orphan*/  evrpc_pool_set_timeout (struct evrpc_pool*,int) ; 
 int /*<<< orphan*/  from_name ; 
 int /*<<< orphan*/  kill_free (struct kill*) ; 
 struct kill* kill_new () ; 
 int /*<<< orphan*/  msg_free (struct msg*) ; 
 struct msg* msg_new () ; 
 struct evrpc_pool* rpc_pool_with_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_setup (struct evhttp**,int /*<<< orphan*/ *,struct evrpc_base**) ; 
 int /*<<< orphan*/  rpc_teardown (struct evrpc_base*) ; 
 int /*<<< orphan*/  saved_rpc ; 
 int test_ok ; 
 int /*<<< orphan*/  to_name ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
rpc_client_timeout(void)
{
	ev_uint16_t port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;
	struct evrpc_pool *pool = NULL;
	struct msg *msg = NULL;
	struct kill *kill = NULL;

	rpc_setup(&http, &port, &base);

	pool = rpc_pool_with_connection(port);
	tt_assert(pool);

	/* set the timeout to 1 second. */
	evrpc_pool_set_timeout(pool, 1);

	/* set up the basic message */
	msg = msg_new();
	tt_assert(msg);
	EVTAG_ASSIGN(msg, from_name, "niels");
	EVTAG_ASSIGN(msg, to_name, "tester");

	kill = kill_new();

	EVRPC_MAKE_REQUEST(NeverReply, pool, msg, kill, GotErrorCb, NULL);

	test_ok = 0;

	event_dispatch();

	/* free the saved RPC structure up */
	EVRPC_REQUEST_DONE(saved_rpc);

	rpc_teardown(base);

	tt_assert(test_ok == 2);

end:
	if (msg)
		msg_free(msg);
	if (kill)
		kill_free(kill);

	if (pool)
		evrpc_pool_free(pool);
	if (http)
		evhttp_free(http);
}