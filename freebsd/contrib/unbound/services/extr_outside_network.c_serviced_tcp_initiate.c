#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serviced_query {scalar_t__ status; int /*<<< orphan*/  pending; TYPE_1__* outnet; int /*<<< orphan*/  last_sent_time; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/ * now_tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_CLOSED ; 
 int /*<<< orphan*/  TCP_AUTH_QUERY_TIMEOUT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  pending_tcp_query (struct serviced_query*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct serviced_query*) ; 
 int /*<<< orphan*/  serviced_callbacks (struct serviced_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serviced_encode (struct serviced_query*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ serviced_query_TCP_EDNS ; 
 int /*<<< orphan*/  serviced_tcp_callback ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
serviced_tcp_initiate(struct serviced_query* sq, sldns_buffer* buff)
{
	verbose(VERB_ALGO, "initiate TCP query %s", 
		sq->status==serviced_query_TCP_EDNS?"EDNS":"");
	serviced_encode(sq, buff, sq->status == serviced_query_TCP_EDNS);
	sq->last_sent_time = *sq->outnet->now_tv;
	sq->pending = pending_tcp_query(sq, buff, TCP_AUTH_QUERY_TIMEOUT,
		serviced_tcp_callback, sq);
	if(!sq->pending) {
		/* delete from tree so that a retry by above layer does not
		 * clash with this entry */
		verbose(VERB_ALGO, "serviced_tcp_initiate: failed to send tcp query");
		serviced_callbacks(sq, NETEVENT_CLOSED, NULL, NULL);
	}
}