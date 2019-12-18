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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct evdns_server_request {int nquestions; TYPE_1__** questions; } ;
struct TYPE_2__ {int type; int dns_question_class; char* name; } ;

/* Variables and functions */
 int const EVDNS_CLASS_INET ; 
 int const EVDNS_TYPE_A ; 
 int const EVDNS_TYPE_AAAA ; 
 int const EVDNS_TYPE_PTR ; 
 scalar_t__ dns_ok ; 
 int evdns_server_request_add_a_reply (struct evdns_server_request*,char const*,int,int /*<<< orphan*/ *,int) ; 
 int evdns_server_request_add_aaaa_reply (struct evdns_server_request*,char const*,int,char*,int) ; 
 int evdns_server_request_add_ptr_reply (struct evdns_server_request*,int /*<<< orphan*/ *,char const*,char*,int) ; 
 scalar_t__ evdns_server_request_drop (struct evdns_server_request*) ; 
 int evdns_server_request_respond (struct evdns_server_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_ascii_strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dns_server_request_cb(struct evdns_server_request *req, void *data)
{
	int i, r;
	const char TEST_ARPA[] = "11.11.168.192.in-addr.arpa";
	const char TEST_IN6[] =
	    "f.e.f.e." "0.0.0.0." "0.0.0.0." "1.1.1.1."
	    "a.a.a.a." "0.0.0.0." "0.0.0.0." "0.f.f.f.ip6.arpa";

	for (i = 0; i < req->nquestions; ++i) {
		const int qtype = req->questions[i]->type;
		const int qclass = req->questions[i]->dns_question_class;
		const char *qname = req->questions[i]->name;

		struct in_addr ans;
		ans.s_addr = htonl(0xc0a80b0bUL); /* 192.168.11.11 */
		if (qtype == EVDNS_TYPE_A &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, "zz.example.com")) {
			r = evdns_server_request_add_a_reply(req, qname,
			    1, &ans.s_addr, 12345);
			if (r<0)
				dns_ok = 0;
		} else if (qtype == EVDNS_TYPE_AAAA &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, "zz.example.com")) {
			char addr6[17] = "abcdefghijklmnop";
			r = evdns_server_request_add_aaaa_reply(req,
			    qname, 1, addr6, 123);
			if (r<0)
				dns_ok = 0;
		} else if (qtype == EVDNS_TYPE_PTR &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, TEST_ARPA)) {
			r = evdns_server_request_add_ptr_reply(req, NULL,
			    qname, "ZZ.EXAMPLE.COM", 54321);
			if (r<0)
				dns_ok = 0;
		} else if (qtype == EVDNS_TYPE_PTR &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, TEST_IN6)){
			r = evdns_server_request_add_ptr_reply(req, NULL,
			    qname,
			    "ZZ-INET6.EXAMPLE.COM", 54322);
			if (r<0)
				dns_ok = 0;
		} else if (qtype == EVDNS_TYPE_A &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, "drop.example.com")) {
			if (evdns_server_request_drop(req)<0)
				dns_ok = 0;
			return;
		} else {
			printf("Unexpected question %d %d \"%s\" ",
			    qtype, qclass, qname);
			dns_ok = 0;
		}
	}
	r = evdns_server_request_respond(req, 0);
	if (r<0) {
		printf("Couldn't send reply. ");
		dns_ok = 0;
	}
}