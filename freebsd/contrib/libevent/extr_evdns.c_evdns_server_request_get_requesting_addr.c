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
struct sockaddr {int dummy; } ;
struct server_request {int addrlen; int /*<<< orphan*/  addr; } ;
struct evdns_server_request {int dummy; } ;

/* Variables and functions */
 struct server_request* TO_SERVER_REQUEST (struct evdns_server_request*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,int) ; 

int
evdns_server_request_get_requesting_addr(struct evdns_server_request *req_, struct sockaddr *sa, int addr_len)
{
	struct server_request *req = TO_SERVER_REQUEST(req_);
	if (addr_len < (int)req->addrlen)
		return -1;
	memcpy(sa, &(req->addr), req->addrlen);
	return req->addrlen;
}