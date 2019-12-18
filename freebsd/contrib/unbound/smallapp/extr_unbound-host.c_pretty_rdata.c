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

/* Variables and functions */
 int LDNS_RR_TYPE_A ; 
 int LDNS_RR_TYPE_AAAA ; 
 int LDNS_RR_TYPE_MX ; 
 int LDNS_RR_TYPE_PTR ; 
 int /*<<< orphan*/  print_rd (int,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
pretty_rdata(char* q, char* cstr, char* tstr, int t, const char* sec, 
	char* data, size_t len)
{
	printf("%s", q);
	if(strcmp(cstr, "IN") != 0)
		printf(" in class %s", cstr);
	if(t == LDNS_RR_TYPE_A)
		printf(" has address");
	else if(t == LDNS_RR_TYPE_AAAA)
		printf(" has IPv6 address");
	else if(t == LDNS_RR_TYPE_MX)
		printf(" mail is handled by");
	else if(t == LDNS_RR_TYPE_PTR)
		printf(" domain name pointer");
	else	printf(" has %s record", tstr);
	print_rd(t, data, len);
	if(verb > 0)
		printf(" %s", sec);
	printf("\n");
}