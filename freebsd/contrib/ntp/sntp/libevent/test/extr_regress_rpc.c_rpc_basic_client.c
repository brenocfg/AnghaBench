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
struct evrpc_request_wrapper {int dummy; } ;
struct evrpc_pool {int dummy; } ;
typedef  struct evrpc_pool evrpc_base ;
struct evhttp {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_INPUT ; 
 struct evrpc_request_wrapper* EVRPC_MAKE_CTX (int /*<<< orphan*/ ,struct msg*,struct kill*,struct evrpc_pool*,struct msg*,struct kill*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVRPC_MAKE_REQUEST (int /*<<< orphan*/ ,struct evrpc_pool*,struct msg*,struct kill*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVRPC_OUTPUT ; 
 int /*<<< orphan*/  EVTAG_ASSIGN (struct msg*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GotKillCb ; 
 int /*<<< orphan*/  Message ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int /*<<< orphan*/ * evrpc_add_hook (struct evrpc_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evrpc_make_request (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  evrpc_pool_free (struct evrpc_pool*) ; 
 int /*<<< orphan*/  from_name ; 
 int /*<<< orphan*/  kill_clear (struct kill*) ; 
 int /*<<< orphan*/  kill_free (struct kill*) ; 
 struct kill* kill_new () ; 
 int /*<<< orphan*/  msg_free (struct msg*) ; 
 struct msg* msg_new () ; 
 int need_input_hook ; 
 int need_output_hook ; 
 int /*<<< orphan*/  rpc_hook_add_header ; 
 int /*<<< orphan*/  rpc_hook_add_meta ; 
 int /*<<< orphan*/  rpc_hook_remove_header ; 
 struct evrpc_pool* rpc_pool_with_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_setup (struct evhttp**,int /*<<< orphan*/ *,struct evrpc_pool**) ; 
 int /*<<< orphan*/  rpc_teardown (struct evrpc_pool*) ; 
 int test_ok ; 
 int /*<<< orphan*/  to_name ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
rpc_basic_client(void)
{
	ev_uint16_t port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;
	struct evrpc_pool *pool = NULL;
	struct msg *msg = NULL;
	struct kill *kill = NULL;

	rpc_setup(&http, &port, &base);

	need_input_hook = 1;
	need_output_hook = 1;

	assert(evrpc_add_hook(base, EVRPC_INPUT, rpc_hook_add_header, (void*)"input")
	    != NULL);
	assert(evrpc_add_hook(base, EVRPC_OUTPUT, rpc_hook_add_header, (void*)"output")
	    != NULL);

	pool = rpc_pool_with_connection(port);
	tt_assert(pool);

	assert(evrpc_add_hook(pool, EVRPC_OUTPUT, rpc_hook_add_meta, NULL));
	assert(evrpc_add_hook(pool, EVRPC_INPUT, rpc_hook_remove_header, (void*)"output"));

	/* set up the basic message */
	msg = msg_new();
	tt_assert(msg);
	EVTAG_ASSIGN(msg, from_name, "niels");
	EVTAG_ASSIGN(msg, to_name, "tester");

	kill = kill_new();

	EVRPC_MAKE_REQUEST(Message, pool, msg, kill,  GotKillCb, NULL);

	test_ok = 0;

	event_dispatch();

	tt_assert(test_ok == 1);

	/* we do it twice to make sure that reuse works correctly */
	kill_clear(kill);

	EVRPC_MAKE_REQUEST(Message, pool, msg, kill,  GotKillCb, NULL);

	event_dispatch();

	tt_assert(test_ok == 2);

	/* we do it trice to make sure other stuff works, too */
	kill_clear(kill);

	{
		struct evrpc_request_wrapper *ctx =
		    EVRPC_MAKE_CTX(Message, msg, kill,
			pool, msg, kill, GotKillCb, NULL);
		evrpc_make_request(ctx);
	}

	event_dispatch();

	rpc_teardown(base);

	tt_assert(test_ok == 3);

end:
	if (msg)
		msg_free(msg);
	if (kill)
		kill_free(kill);

	if (pool)
		evrpc_pool_free(pool);
	if (http)
		evhttp_free(http);

	need_input_hook = 0;
	need_output_hook = 0;
}