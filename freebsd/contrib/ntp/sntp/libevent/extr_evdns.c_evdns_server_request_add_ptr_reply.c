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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct evdns_server_request {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ a ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_INET ; 
 int /*<<< orphan*/  EVDNS_ANSWER_SECTION ; 
 int /*<<< orphan*/  TYPE_PTR ; 
 int evdns_server_request_add_reply (struct evdns_server_request*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char const*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int,int,int,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int
evdns_server_request_add_ptr_reply(struct evdns_server_request *req, struct in_addr *in, const char *inaddr_name, const char *hostname, int ttl)
{
	u32 a;
	char buf[32];
	if (in && inaddr_name)
		return -1;
	else if (!in && !inaddr_name)
		return -1;
	if (in) {
		a = ntohl(in->s_addr);
		evutil_snprintf(buf, sizeof(buf), "%d.%d.%d.%d.in-addr.arpa",
				(int)(u8)((a	)&0xff),
				(int)(u8)((a>>8 )&0xff),
				(int)(u8)((a>>16)&0xff),
				(int)(u8)((a>>24)&0xff));
		inaddr_name = buf;
	}
	return evdns_server_request_add_reply(
		  req, EVDNS_ANSWER_SECTION, inaddr_name, TYPE_PTR, CLASS_INET,
		  ttl, -1, 1, hostname);
}