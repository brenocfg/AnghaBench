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
struct hostent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int IN6ADDRSZ ; 
 int INADDRSZ ; 
 int RV_NOTFOUND ; 
 int RV_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endhostent () ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 struct hostent* gethostbyname2 (char*,int /*<<< orphan*/ ) ; 
 struct hostent* gethostent () ; 
 int /*<<< orphan*/  hostsprint (struct hostent*) ; 
 scalar_t__ inet_pton (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  sethostent (int) ; 

__attribute__((used)) static int
hosts(int argc, char *argv[])
{
	struct hostent	*he4, *he6;
	char		addr[IN6ADDRSZ];
	int		i, rv;

	assert(argc > 1);
	assert(argv != NULL);

	sethostent(1);
	he4 = he6 = NULL;
	rv = RV_OK;
	if (argc == 2) {
		while ((he4 = gethostent()) != NULL)
			hostsprint(he4);
	} else {
		for (i = 2; i < argc; i++) {
			if (inet_pton(AF_INET6, argv[i], (void *)addr) > 0) {
				he6 = gethostbyaddr(addr, IN6ADDRSZ, AF_INET6);
				if (he6 != NULL)
					hostsprint(he6);
			} else if (inet_pton(AF_INET, argv[i],
			    (void *)addr) > 0) {
				he4 = gethostbyaddr(addr, INADDRSZ, AF_INET);
				if (he4 != NULL)
					hostsprint(he4);
	       		} else {
				he6 = gethostbyname2(argv[i], AF_INET6);
				if (he6 != NULL)
					hostsprint(he6);
				he4 = gethostbyname(argv[i]);
				if (he4 != NULL)
					hostsprint(he4);
			}
			if ( he4 == NULL && he6 == NULL ) {
				rv = RV_NOTFOUND;
				break;
			}
		}
	}
	endhostent();
	return rv;
}