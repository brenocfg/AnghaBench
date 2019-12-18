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
struct evrpc_base {int dummy; } ;
struct evhttp {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_REGISTER (struct evrpc_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Message ; 
 int /*<<< orphan*/  MessageCb ; 
 int /*<<< orphan*/  NeverReply ; 
 int /*<<< orphan*/  NeverReplyCb ; 
 struct evrpc_base* evrpc_init (struct evhttp*) ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill ; 
 int /*<<< orphan*/  msg ; 
 scalar_t__ need_input_hook ; 
 scalar_t__ need_output_hook ; 

__attribute__((used)) static void
rpc_setup(struct evhttp **phttp, ev_uint16_t *pport, struct evrpc_base **pbase)
{
	ev_uint16_t port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;

	http = http_setup(&port);
	base = evrpc_init(http);

	EVRPC_REGISTER(base, Message, msg, kill, MessageCb, NULL);
	EVRPC_REGISTER(base, NeverReply, msg, kill, NeverReplyCb, NULL);

	*phttp = http;
	*pport = port;
	*pbase = base;

	need_input_hook = 0;
	need_output_hook = 0;
}