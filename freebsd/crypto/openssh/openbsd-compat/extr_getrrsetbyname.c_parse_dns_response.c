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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int qdcount; int ancount; int nscount; int arcount; } ;
struct dns_response {int /*<<< orphan*/ * additional; TYPE_1__ header; int /*<<< orphan*/ * authority; int /*<<< orphan*/ * answer; int /*<<< orphan*/ * query; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFIXEDSZ ; 
 struct dns_response* calloc (int,int) ; 
 int /*<<< orphan*/  free_dns_response (struct dns_response*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* ntohs (int) ; 
 int /*<<< orphan*/ * parse_dns_qsection (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**,int) ; 
 void* parse_dns_rrsection (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static struct dns_response *
parse_dns_response(const u_char *answer, int size)
{
	struct dns_response *resp;
	const u_char *cp;

	/* allocate memory for the response */
	resp = calloc(1, sizeof(*resp));
	if (resp == NULL)
		return (NULL);

	/* initialize current pointer */
	cp = answer;

	/* copy header */
	memcpy(&resp->header, cp, HFIXEDSZ);
	cp += HFIXEDSZ;

	/* fix header byte order */
	resp->header.qdcount = ntohs(resp->header.qdcount);
	resp->header.ancount = ntohs(resp->header.ancount);
	resp->header.nscount = ntohs(resp->header.nscount);
	resp->header.arcount = ntohs(resp->header.arcount);

	/* there must be at least one query */
	if (resp->header.qdcount < 1) {
		free_dns_response(resp);
		return (NULL);
	}

	/* parse query section */
	resp->query = parse_dns_qsection(answer, size, &cp,
	    resp->header.qdcount);
	if (resp->header.qdcount && resp->query == NULL) {
		free_dns_response(resp);
		return (NULL);
	}

	/* parse answer section */
	resp->answer = parse_dns_rrsection(answer, size, &cp,
	    resp->header.ancount);
	if (resp->header.ancount && resp->answer == NULL) {
		free_dns_response(resp);
		return (NULL);
	}

	/* parse authority section */
	resp->authority = parse_dns_rrsection(answer, size, &cp,
	    resp->header.nscount);
	if (resp->header.nscount && resp->authority == NULL) {
		free_dns_response(resp);
		return (NULL);
	}

	/* parse additional section */
	resp->additional = parse_dns_rrsection(answer, size, &cp,
	    resp->header.arcount);
	if (resp->header.arcount && resp->additional == NULL) {
		free_dns_response(resp);
		return (NULL);
	}

	return (resp);
}