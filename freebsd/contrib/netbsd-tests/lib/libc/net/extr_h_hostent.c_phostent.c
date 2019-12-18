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
struct hostent {scalar_t__ h_length; char* h_name; int h_addrtype; scalar_t__* h_addr_list; scalar_t__* h_aliases; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ NS_INADDRSZ ; 
 int /*<<< orphan*/  inet_ntop (int const,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
phostent(const struct hostent *h)
{
	size_t i;
	char buf[1024];
	const int af = h->h_length == NS_INADDRSZ ? AF_INET : AF_INET6;

	printf("name=%s, length=%d, addrtype=%d, aliases=[",
	    h->h_name, h->h_length, h->h_addrtype);

	for (i = 0; h->h_aliases[i]; i++)
		printf("%s%s", i == 0 ? "" : " ", h->h_aliases[i]);

	printf("] addr_list=[");

	for (i = 0; h->h_addr_list[i]; i++)
		printf("%s%s", i == 0 ? "" : " ", inet_ntop(af,
		    h->h_addr_list[i], buf, (socklen_t)sizeof(buf)));

	printf("]\n");
}