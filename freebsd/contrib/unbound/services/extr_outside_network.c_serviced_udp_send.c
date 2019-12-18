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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct serviced_query {int last_rtt; scalar_t__ status; int edns_lame_known; int /*<<< orphan*/  pending; TYPE_1__* outnet; int /*<<< orphan*/  last_sent_time; int /*<<< orphan*/  zonelen; int /*<<< orphan*/  zone; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/ * now_tv; int /*<<< orphan*/  infra; int /*<<< orphan*/ * now_secs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  infra_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  pending_udp_query (struct serviced_query*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct serviced_query*) ; 
 int /*<<< orphan*/  serviced_encode (struct serviced_query*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ serviced_initial ; 
 scalar_t__ serviced_query_UDP ; 
 scalar_t__ serviced_query_UDP_EDNS ; 
 scalar_t__ serviced_query_UDP_EDNS_FRAG ; 
 int /*<<< orphan*/  serviced_udp_callback ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
serviced_udp_send(struct serviced_query* sq, sldns_buffer* buff)
{
	int rtt, vs;
	uint8_t edns_lame_known;
	time_t now = *sq->outnet->now_secs;

	if(!infra_host(sq->outnet->infra, &sq->addr, sq->addrlen, sq->zone,
		sq->zonelen, now, &vs, &edns_lame_known, &rtt))
		return 0;
	sq->last_rtt = rtt;
	verbose(VERB_ALGO, "EDNS lookup known=%d vs=%d", edns_lame_known, vs);
	if(sq->status == serviced_initial) {
		if(vs != -1) {
			sq->status = serviced_query_UDP_EDNS;
		} else { 	
			sq->status = serviced_query_UDP; 
		}
	}
	serviced_encode(sq, buff, (sq->status == serviced_query_UDP_EDNS) ||
		(sq->status == serviced_query_UDP_EDNS_FRAG));
	sq->last_sent_time = *sq->outnet->now_tv;
	sq->edns_lame_known = (int)edns_lame_known;
	verbose(VERB_ALGO, "serviced query UDP timeout=%d msec", rtt);
	sq->pending = pending_udp_query(sq, buff, rtt,
		serviced_udp_callback, sq);
	if(!sq->pending)
		return 0;
	return 1;
}