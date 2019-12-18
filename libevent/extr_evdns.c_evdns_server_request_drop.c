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
struct server_request {int dummy; } ;
struct evdns_server_request {int dummy; } ;

/* Variables and functions */
 struct server_request* TO_SERVER_REQUEST (struct evdns_server_request*) ; 
 int /*<<< orphan*/  server_request_free (struct server_request*) ; 

int
evdns_server_request_drop(struct evdns_server_request *req_)
{
	struct server_request *req = TO_SERVER_REQUEST(req_);
	server_request_free(req);
	return 0;
}