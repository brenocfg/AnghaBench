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
struct ub_result {int rcode; char const* why_bogus; char* canonname; char* qname; scalar_t__ bogus; scalar_t__* len; scalar_t__* data; scalar_t__ answer_len; int /*<<< orphan*/  answer_packet; int /*<<< orphan*/  havedata; } ;

/* Variables and functions */
 int LDNS_RR_TYPE_A ; 
 int LDNS_RR_TYPE_AAAA ; 
 int LDNS_RR_TYPE_ANY ; 
 int LDNS_RR_TYPE_MX ; 
 int LDNS_RR_TYPE_PTR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pretty_class (char*,int,int) ; 
 int /*<<< orphan*/  pretty_rcode (char*,int,int) ; 
 int /*<<< orphan*/  pretty_rdata (char*,char*,char*,int,char const*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  pretty_type (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* secure_str (struct ub_result*) ; 
 char* sldns_wire2str_pkt (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
pretty_output(char* q, int t, int c, struct ub_result* result, int docname)
{
	int i;
	const char *secstatus = secure_str(result);
	char tstr[16];
	char cstr[16];
	char rcodestr[16];
	pretty_type(tstr, 16, t);
	pretty_class(cstr, 16, c);
	pretty_rcode(rcodestr, 16, result->rcode);

	if(!result->havedata && result->rcode) {
		printf("Host %s not found: %d(%s).",
			q, result->rcode, rcodestr);
		if(verb > 0)
			printf(" %s", secstatus);
		printf("\n");
		if(result->bogus && result->why_bogus)
			printf("%s\n", result->why_bogus);
		return;
	}
	if(docname && result->canonname &&
		result->canonname != result->qname) {
		printf("%s is an alias for %s", result->qname, 
			result->canonname);
		if(verb > 0)
			printf(" %s", secstatus);
		printf("\n");
	}
	/* remove trailing . from long canonnames for nicer output */
	if(result->canonname && strlen(result->canonname) > 1 &&
		result->canonname[strlen(result->canonname)-1] == '.')
		result->canonname[strlen(result->canonname)-1] = 0;
	if(!result->havedata) {
		if(verb > 0) {
			printf("%s", result->canonname?result->canonname:q);
			if(strcmp(cstr, "IN") != 0)
				printf(" in class %s", cstr);
			if(t == LDNS_RR_TYPE_A)
				printf(" has no address");
			else if(t == LDNS_RR_TYPE_AAAA)
				printf(" has no IPv6 address");
			else if(t == LDNS_RR_TYPE_PTR)
				printf(" has no domain name ptr");
			else if(t == LDNS_RR_TYPE_MX)
				printf(" has no mail handler record");
			else if(t == LDNS_RR_TYPE_ANY) {
				char* s = sldns_wire2str_pkt(
					result->answer_packet,
					(size_t)result->answer_len);
				if(!s) {
					fprintf(stderr, "alloc failure\n");
					exit(1);
				}
				printf("%s\n", s);
				free(s);
			} else	printf(" has no %s record", tstr);
			printf(" %s\n", secstatus);
		}
		/* else: emptiness to indicate no data */
		if(result->bogus && result->why_bogus)
			printf("%s\n", result->why_bogus);
		return;
	}
	i=0;
	while(result->data[i])
	{
		pretty_rdata(
			result->canonname?result->canonname:q,
			cstr, tstr, t, secstatus, result->data[i],
			(size_t)result->len[i]);
		i++;
	}
	if(result->bogus && result->why_bogus)
		printf("%s\n", result->why_bogus);
}