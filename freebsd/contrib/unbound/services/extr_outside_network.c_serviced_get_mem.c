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
struct serviced_query {int qbuflen; scalar_t__ status; struct service_callback* cblist; } ;
struct service_callback {struct service_callback* next; } ;
struct pending {int dummy; } ;

/* Variables and functions */
 scalar_t__ comm_timer_get_mem (int /*<<< orphan*/ *) ; 
 scalar_t__ serviced_query_UDP ; 
 scalar_t__ serviced_query_UDP_EDNS ; 
 scalar_t__ serviced_query_UDP_EDNS_FRAG ; 
 scalar_t__ serviced_query_UDP_EDNS_fallback ; 

size_t 
serviced_get_mem(struct serviced_query* sq)
{
	struct service_callback* sb;
	size_t s;
	s = sizeof(*sq) + sq->qbuflen;
	for(sb = sq->cblist; sb; sb = sb->next)
		s += sizeof(*sb);
	if(sq->status == serviced_query_UDP_EDNS ||
		sq->status == serviced_query_UDP ||
		sq->status == serviced_query_UDP_EDNS_FRAG ||
		sq->status == serviced_query_UDP_EDNS_fallback) {
		s += sizeof(struct pending);
		s += comm_timer_get_mem(NULL);
	} else {
		/* does not have size of the pkt pointer */
		/* always has a timer except on malloc failures */

		/* these sizes are part of the main outside network mem */
		/*
		s += sizeof(struct waiting_tcp);
		s += comm_timer_get_mem(NULL);
		*/
	}
	return s;
}