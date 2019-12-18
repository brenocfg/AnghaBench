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
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;

/* Variables and functions */
 int RESTRICTED_SERVERS ; 
 int /*<<< orphan*/  YPSET_NO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* domain_name ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/ * restricted_addrs ; 
 char* strsep (char**,char*) ; 
 int yp_restricted ; 
 int /*<<< orphan*/  ypsetmode ; 

void
yp_restricted_mode(char *args)
{
	struct hostent *h;
	int i = 0;
	char *s;

	/* Find the restricted domain. */
	if ((s = strsep(&args, ",")) == NULL)
		return;
	domain_name = s;

	/* Get the addresses of the servers. */
	while ((s = strsep(&args, ",")) != NULL && i < RESTRICTED_SERVERS) {
		if ((h = gethostbyname(s)) == NULL)
			return;
		bcopy (h->h_addr_list[0], &restricted_addrs[i],
		    sizeof(struct in_addr));
		i++;
	}

	/* ypset and ypsetme not allowed with restricted mode */
	ypsetmode = YPSET_NO;

	yp_restricted = i;
	return;
}