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
typedef  scalar_t__ uint8_t ;
struct regional {int dummy; } ;
struct edns_data {int /*<<< orphan*/  opt_list; } ;
struct comm_point {scalar_t__ type; int tcp_keepalive; int tcp_timeout_msec; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_EDNS_KEEPALIVE ; 
 scalar_t__ comm_udp ; 
 int /*<<< orphan*/  edns_opt_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*,struct regional*) ; 
 scalar_t__ edns_opt_list_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edns_keepalive(struct edns_data* edns_out, struct edns_data* edns_in,
		struct comm_point* c, struct regional* region)
{
	if(c->type == comm_udp)
		return 1;

	/* To respond with a Keepalive option, the client connection
	 * must have received one message with a TCP Keepalive EDNS option,
	 * and that option must have 0 length data. Subsequent messages
	 * sent on that connection will have a TCP Keepalive option.
	 */
	if(c->tcp_keepalive ||
		edns_opt_list_find(edns_in->opt_list, LDNS_EDNS_KEEPALIVE)) {
		int keepalive = c->tcp_timeout_msec / 100;
		uint8_t data[2];
		data[0] = (uint8_t)((keepalive >> 8) & 0xff);
		data[1] = (uint8_t)(keepalive & 0xff);
		if(!edns_opt_list_append(&edns_out->opt_list, LDNS_EDNS_KEEPALIVE,
			sizeof(data), data, region))
			return 0;
		c->tcp_keepalive = 1;
	}
	return 1;
}