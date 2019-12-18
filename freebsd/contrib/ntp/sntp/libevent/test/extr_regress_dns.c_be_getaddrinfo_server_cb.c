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
struct in_addr {void* s_addr; } ;
struct in6_addr {int* s6_addr; } ;
struct evdns_server_request {int nquestions; TYPE_1__** questions; } ;
typedef  int /*<<< orphan*/  ans6 ;
struct TYPE_2__ {int type; int dns_question_class; char* name; } ;

/* Variables and functions */
 int const EVDNS_CLASS_INET ; 
 int const EVDNS_TYPE_A ; 
 int const EVDNS_TYPE_AAAA ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  TT_FAIL (char*) ; 
 int /*<<< orphan*/  TT_GRIPE (char*) ; 
 int /*<<< orphan*/  evdns_server_request_add_a_reply (struct evdns_server_request*,char const*,int,void**,int) ; 
 int /*<<< orphan*/  evdns_server_request_add_aaaa_reply (struct evdns_server_request*,char const*,int,int**,int) ; 
 int /*<<< orphan*/  evdns_server_request_add_cname_reply (struct evdns_server_request*,char const*,char*,int) ; 
 int /*<<< orphan*/  evdns_server_request_drop (struct evdns_server_request*) ; 
 int /*<<< orphan*/  evdns_server_request_respond (struct evdns_server_request*,int) ; 
 int /*<<< orphan*/  evutil_ascii_strcasecmp (char const*,char*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
be_getaddrinfo_server_cb(struct evdns_server_request *req, void *data)
{
	int i;
	int *n_got_p=data;
	int added_any=0;
	++*n_got_p;

	for (i=0;i<req->nquestions;++i) {
		const int qtype = req->questions[i]->type;
		const int qclass = req->questions[i]->dns_question_class;
		const char *qname = req->questions[i]->name;
		struct in_addr ans;
		struct in6_addr ans6;
		memset(&ans6, 0, sizeof(ans6));

		TT_BLATHER(("Got question about %s, type=%d", qname, qtype));

		if (qtype == EVDNS_TYPE_A &&
		    qclass == EVDNS_CLASS_INET &&
		    !evutil_ascii_strcasecmp(qname, "nobodaddy.example.com")) {
			ans.s_addr = htonl(0x7f000001);
			evdns_server_request_add_a_reply(req, qname,
			    1, &ans.s_addr, 2000);
			added_any = 1;
		} else if (!evutil_ascii_strcasecmp(qname,
			"nosuchplace.example.com")) {
			/* ok, just say notfound. */
		} else if (!evutil_ascii_strcasecmp(qname,
			"both.example.com")) {
			if (qtype == EVDNS_TYPE_A) {
				ans.s_addr = htonl(0x50502020);
				evdns_server_request_add_a_reply(req, qname,
				    1, &ans.s_addr, 2000);
				added_any = 1;
			} else if (qtype == EVDNS_TYPE_AAAA) {
				ans6.s6_addr[0] = 0x80;
				ans6.s6_addr[1] = 0xff;
				ans6.s6_addr[14] = 0xbb;
				ans6.s6_addr[15] = 0xbb;
				evdns_server_request_add_aaaa_reply(req, qname,
				    1, &ans6.s6_addr, 2000);
				added_any = 1;
			}
			evdns_server_request_add_cname_reply(req, qname,
			    "both-canonical.example.com", 1000);
		} else if (!evutil_ascii_strcasecmp(qname,
			"v4only.example.com") ||
		    !evutil_ascii_strcasecmp(qname, "v4assert.example.com")) {
			if (qtype == EVDNS_TYPE_A) {
				ans.s_addr = htonl(0x12345678);
				evdns_server_request_add_a_reply(req, qname,
				    1, &ans.s_addr, 2000);
				added_any = 1;
			} else if (!evutil_ascii_strcasecmp(qname,
				"v4assert.example.com")) {
				TT_FAIL(("Got an AAAA request for v4assert"));
			}
		} else if (!evutil_ascii_strcasecmp(qname,
			"v6only.example.com") ||
		    !evutil_ascii_strcasecmp(qname, "v6assert.example.com")) {
			if (qtype == EVDNS_TYPE_AAAA) {
				ans6.s6_addr[0] = 0x0b;
				ans6.s6_addr[1] = 0x0b;
				ans6.s6_addr[14] = 0xf0;
				ans6.s6_addr[15] = 0x0d;
				evdns_server_request_add_aaaa_reply(req, qname,
				    1, &ans6.s6_addr, 2000);
				added_any = 1;
			}  else if (!evutil_ascii_strcasecmp(qname,
				"v6assert.example.com")) {
				TT_FAIL(("Got a A request for v6assert"));
			}
		} else if (!evutil_ascii_strcasecmp(qname,
			"v6timeout.example.com")) {
			if (qtype == EVDNS_TYPE_A) {
				ans.s_addr = htonl(0xabcdef01);
				evdns_server_request_add_a_reply(req, qname,
				    1, &ans.s_addr, 2000);
				added_any = 1;
			} else if (qtype == EVDNS_TYPE_AAAA) {
				/* Let the v6 request time out.*/
				evdns_server_request_drop(req);
				return;
			}
		} else if (!evutil_ascii_strcasecmp(qname,
			"v4timeout.example.com")) {
			if (qtype == EVDNS_TYPE_AAAA) {
				ans6.s6_addr[0] = 0x0a;
				ans6.s6_addr[1] = 0x0a;
				ans6.s6_addr[14] = 0xff;
				ans6.s6_addr[15] = 0x01;
				evdns_server_request_add_aaaa_reply(req, qname,
				    1, &ans6.s6_addr, 2000);
				added_any = 1;
			} else if (qtype == EVDNS_TYPE_A) {
				/* Let the v4 request time out.*/
				evdns_server_request_drop(req);
				return;
			}
		} else if (!evutil_ascii_strcasecmp(qname,
			"v6timeout-nonexist.example.com")) {
			if (qtype == EVDNS_TYPE_A) {
				/* Fall through, give an nexist. */
			} else if (qtype == EVDNS_TYPE_AAAA) {
				/* Let the v6 request time out.*/
				evdns_server_request_drop(req);
				return;
			}
		} else if (!evutil_ascii_strcasecmp(qname,
			"all-timeout.example.com")) {
			/* drop all requests */
			evdns_server_request_drop(req);
			return;
		} else {
			TT_GRIPE(("Got weird request for %s",qname));
		}
	}
	if (added_any) {
		TT_BLATHER(("answering"));
		evdns_server_request_respond(req, 0);
	} else {
		TT_BLATHER(("saying nexist."));
		evdns_server_request_respond(req, 3);
	}
}