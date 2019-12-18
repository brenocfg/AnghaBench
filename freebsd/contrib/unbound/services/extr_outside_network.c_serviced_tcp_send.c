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
typedef  int /*<<< orphan*/  uint8_t ;
struct serviced_query {int last_rtt; scalar_t__ status; int /*<<< orphan*/ * pending; scalar_t__ ssl_upstream; scalar_t__ tcp_upstream; TYPE_1__* outnet; int /*<<< orphan*/  last_sent_time; int /*<<< orphan*/  zonelen; int /*<<< orphan*/  zone; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/ * now_tv; int /*<<< orphan*/ * now_secs; int /*<<< orphan*/  infra; } ;

/* Variables and functions */
 int TCP_AUTH_QUERY_TIMEOUT ; 
 int UNKNOWN_SERVER_NICENESS ; 
 int /*<<< orphan*/  infra_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * pending_tcp_query (struct serviced_query*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct serviced_query*) ; 
 int /*<<< orphan*/  serviced_encode (struct serviced_query*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ serviced_query_TCP ; 
 scalar_t__ serviced_query_TCP_EDNS ; 
 int /*<<< orphan*/  serviced_tcp_callback ; 

__attribute__((used)) static int
serviced_tcp_send(struct serviced_query* sq, sldns_buffer* buff)
{
	int vs, rtt, timeout;
	uint8_t edns_lame_known;
	if(!infra_host(sq->outnet->infra, &sq->addr, sq->addrlen, sq->zone,
		sq->zonelen, *sq->outnet->now_secs, &vs, &edns_lame_known,
		&rtt))
		return 0;
	sq->last_rtt = rtt;
	if(vs != -1)
		sq->status = serviced_query_TCP_EDNS;
	else 	sq->status = serviced_query_TCP;
	serviced_encode(sq, buff, sq->status == serviced_query_TCP_EDNS);
	sq->last_sent_time = *sq->outnet->now_tv;
	if(sq->tcp_upstream || sq->ssl_upstream) {
		timeout = rtt;
		if(rtt >= UNKNOWN_SERVER_NICENESS && rtt < TCP_AUTH_QUERY_TIMEOUT)
			timeout = TCP_AUTH_QUERY_TIMEOUT;
	} else {
		timeout = TCP_AUTH_QUERY_TIMEOUT;
	}
	sq->pending = pending_tcp_query(sq, buff, timeout,
		serviced_tcp_callback, sq);
	return sq->pending != NULL;
}