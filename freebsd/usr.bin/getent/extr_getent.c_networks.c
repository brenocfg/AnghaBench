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
struct netent {int dummy; } ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INADDR_NONE ; 
 int RV_NOTFOUND ; 
 int RV_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endnetent () ; 
 struct netent* getnetbyaddr (scalar_t__,int /*<<< orphan*/ ) ; 
 struct netent* getnetbyname (char*) ; 
 struct netent* getnetent () ; 
 scalar_t__ inet_network (char*) ; 
 int /*<<< orphan*/  networksprint (struct netent*) ; 
 int /*<<< orphan*/  setnetent (int) ; 

__attribute__((used)) static int
networks(int argc, char *argv[])
{
	struct netent	*ne;
	in_addr_t	net;
	int		i, rv;

	assert(argc > 1);
	assert(argv != NULL);

	setnetent(1);
	rv = RV_OK;
	if (argc == 2) {
		while ((ne = getnetent()) != NULL)
			networksprint(ne);
	} else {
		for (i = 2; i < argc; i++) {
			net = inet_network(argv[i]);
			if (net != INADDR_NONE)
				ne = getnetbyaddr(net, AF_INET);
			else
				ne = getnetbyname(argv[i]);
			if (ne != NULL)
				networksprint(ne);
			else {
				rv = RV_NOTFOUND;
				break;
			}
		}
	}
	endnetent();
	return rv;
}