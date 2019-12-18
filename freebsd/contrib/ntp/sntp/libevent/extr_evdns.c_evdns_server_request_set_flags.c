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
struct TYPE_2__ {int flags; } ;
struct server_request {TYPE_1__ base; } ;
struct evdns_server_request {int dummy; } ;

/* Variables and functions */
 int EVDNS_FLAGS_AA ; 
 int EVDNS_FLAGS_RD ; 
 struct server_request* TO_SERVER_REQUEST (struct evdns_server_request*) ; 

void
evdns_server_request_set_flags(struct evdns_server_request *exreq, int flags)
{
	struct server_request *req = TO_SERVER_REQUEST(exreq);
	req->base.flags &= ~(EVDNS_FLAGS_AA|EVDNS_FLAGS_RD);
	req->base.flags |= flags;
}